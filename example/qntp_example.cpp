#include <qntp/NtpClient.h>

#include <cassert>

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtNetwork/QHostInfo>

int main(int argc, char** argv) {
    QCoreApplication loop(argc, argv);
    NtpClient client;

    QObject::connect(&client, &NtpClient::replyReceived, [&](const QHostAddress &address, quint16 port, const NtpReply &reply) {
        qDebug() << "Reply received from " << address << ":" << port << ", transmitTime=" << reply.transmitTime();
        loop.exit(0);
    });

    QTimer::singleShot(10000, &loop, [&]{
        qDebug() << "Timed out";
        loop.exit(1);
    });

    QTimer::singleShot(0, &loop, [&]{
        QHostInfo::lookupHost(QStringLiteral("ntp.pool.org"), [&](const QHostInfo &host){
            if (host.error() != QHostInfo::NoError) {
                qDebug() << "Lookup failed:" << host.errorString();
                loop.exit(1);
                return;
            }

            QList<QHostAddress> addresses = host.addresses();
            for (const QHostAddress &address : addresses)
                qDebug() << "Found address:" << address.toString();
            assert(!addresses.empty());

            if (!client.sendRequest(addresses[0], 123)) {
               qDebug() << "Failed to send NTP request.";
               loop.exit(1);
            }
        });
    });

    return loop.exec();
}
