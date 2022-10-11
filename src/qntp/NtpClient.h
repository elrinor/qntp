#pragma once

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>

#include "NtpEnums.h"
#include "NtpPacket.h"
#include "NtpReply.h"

/**
 * NTP client.
 */
class NtpClient: public QObject {
    Q_OBJECT;
public:
    /**
     * Default constructor.
     *
     * @param parent                   Parent of this object.
     */
    explicit NtpClient(QObject *parent = nullptr): QObject(parent) {
        init(QHostAddress::Any, 0);
    }

    /**
     * Constructor.
     *
     * @param bindAddress              Address to bind udp socket to.
     * @param bindPort                 Port to bind udp socket to.
     * @param parent                   Parent of this object.
     */
    NtpClient(const QHostAddress &bindAddress, quint16 bindPort, QObject *parent = nullptr): QObject(parent) {
        init(bindAddress, bindPort);
    }

    /**
     * Virtual destructor.
     */
    virtual ~NtpClient() {}

    /**
     * Sends NTP request.
     *
     * @param address                  NTP server address.
     * @param port                     NTP server port.
     * @returns                        Whether the NTP request was successfully sent.
     */
    bool sendRequest(const QHostAddress &address, quint16 port) {
        if(m_Socket->state() != QAbstractSocket::BoundState)
            return false;

        /* Initialize the NTP packet. */
        NtpPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.flags.mode = ClientMode;
        packet.flags.versionNumber = 4;
        packet.transmitTimestamp = NtpTimestamp::fromDateTime(QDateTime::currentDateTimeUtc());

        /* Send it. */
        if(m_Socket->writeDatagram(reinterpret_cast<const char *>(&packet), sizeof(packet), address, port) < 0)
            return false;

        return true;
    }

Q_SIGNALS:
    /**
     * This signal is emitted whenever NTP reply is received.
     *
     * @param address                  Address of the server that sent this reply.
     * @param port                     Port of the server that sent this reply.
     * @param reply                    NTP reply.
     */
    void replyReceived(const QHostAddress &address, quint16 port, const NtpReply &reply);

private Q_SLOTS:
    void readPendingDatagrams() {
        while (m_Socket->hasPendingDatagrams()) {
            NtpFullPacket packet;
            memset(&packet, 0, sizeof(packet));

            QHostAddress address;
            quint16 port;
            if (m_Socket->readDatagram(reinterpret_cast<char *>(&packet), sizeof(packet), &address, &port) < sizeof(NtpPacket))
                continue;

            /* Notify. */
            Q_EMIT replyReceived(address, port, NtpReply(packet, QDateTime::currentDateTime()));
        }
    }

private:
    void init(const QHostAddress &bindAddress, quint16 bindPort) {
        m_Socket = new QUdpSocket(this);
        m_Socket->bind(bindAddress, bindPort);

        connect(m_Socket, &QUdpSocket::readyRead, this, &NtpClient::readPendingDatagrams);
    }

    QUdpSocket *m_Socket;
};


