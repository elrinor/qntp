#pragma once

#include <cassert>

#include <memory>

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
    explicit NtpClient(QObject *parent = nullptr): QObject(parent) {}

    /**
     * Virtual destructor.
     */
    virtual ~NtpClient() {}

    /**
     * @param bindAddress              Network address to bind upd socket to. It's passed to `QUdpSocket::bind`.
     * @param bindPort                 Network port to bind udp socket to.
     * @return                         Whether the socket was successfully bound.
     */
    bool bind(const QHostAddress &bindAddress = QHostAddress::Any, quint16 bindPort = 0) {
        m_socket.reset(new QUdpSocket(this));
        if (!m_socket->bind(bindAddress, bindPort))
            return false;

        connect(m_socket.get(), &QUdpSocket::readyRead, this, &NtpClient::readPendingDatagrams);
        return true;
    }

    /**
     * Sends NTP request.
     *
     * @param address                  NTP server address.
     * @param port                     NTP server port.
     * @returns                        Whether the NTP request was successfully sent.
     */
    bool sendRequest(const QHostAddress &address, quint16 port) {
        assert(m_socket->state() == QAbstractSocket::BoundState); // Call bind() first.

        /* Initialize the NTP packet. */
        NtpPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.flags.mode = ClientMode;
        packet.flags.versionNumber = 4;
        packet.transmitTimestamp = NtpTimestamp::fromDateTime(QDateTime::currentDateTimeUtc());

        /* Send it. */
        if(m_socket->writeDatagram(reinterpret_cast<const char *>(&packet), sizeof(packet), address, port) < 0)
            return false;

        return true;
    }

    /**
     * @return                          Underlying `QUdpSocket`. Note that this function might return `nullptr` if
     *                                  `bind` wasn't called.
     */
    const QUdpSocket *socket() const {
        return m_socket.get();
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
        while (m_socket->hasPendingDatagrams()) {
            NtpFullPacket packet;
            memset(&packet, 0, sizeof(packet));

            QHostAddress address;
            quint16 port;
            if (m_socket->readDatagram(reinterpret_cast<char *>(&packet), sizeof(packet), &address, &port) < sizeof(NtpPacket))
                continue;

            Q_EMIT replyReceived(address, port, NtpReply(packet, QDateTime::currentDateTime()));
        }
    }

private:
    std::unique_ptr<QUdpSocket> m_socket;
};


