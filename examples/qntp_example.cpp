#include <qntp/NtpClient.h>

#include <cassert>
#include <cstdio>

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtNetwork/QHostInfo>

int main(int argc, char **argv) {
    QCoreApplication loop(argc, argv);
    QTextStream err(stderr);

    NtpClient client;
    if(!client.bind()) {
        err << "Couldn't bind socket: " << client.socket()->errorString() << "\n";
        return 1;
    }

    QObject::connect(&client, &NtpClient::replyReceived, [&](const QHostAddress &address, quint16 port, const NtpReply &reply) {
        err << "Reply received from " << address.toString() << ":" << port << ": {\n"
            << "    leapIndicator    = " << reply.leapIndicator() << "\n"
            << "    versionNumber    = " << reply.versionNumber() << "\n"
            << "    mode             = " << reply.mode() << "\n"
            << "    stratum          = " << reply.stratum() << "\n"
            << "    pollInterval     = " << reply.pollInterval() << "s\n"
            << "    precision        = " << QString::number(reply.precision(), 10, 15) << "s\n"
            << "    referenceTime    = " << reply.referenceTime().toString(Qt::ISODateWithMs) << "\n"
            << "    originTime       = " << reply.originTime().toString(Qt::ISODateWithMs) << "\n"
            << "    receiveTime      = " << reply.receiveTime().toString(Qt::ISODateWithMs) << "\n"
            << "    transmitTime     = " << reply.transmitTime().toString(Qt::ISODateWithMs) << "\n"
            << "    destinationTime  = " << reply.destinationTime().toString(Qt::ISODateWithMs) << "\n"
            << "    roundTripDelay   = " << reply.roundTripDelay() << "ms\n"
            << "    localClockOffset = " << reply.localClockOffset() << "ms\n"
            << "}\n";
        loop.exit(0);
    });

    QTimer::singleShot(10000, &loop, [&]{
        err << "Timed out\n";
        loop.exit(1);
    });

    QTimer::singleShot(0, &loop, [&]{
        QHostInfo::lookupHost(QStringLiteral("time.euro.apple.com"), [&](const QHostInfo &host){
            if (host.error() != QHostInfo::NoError) {
                err << "Lookup failed: " << host.errorString() << "\n";
                loop.exit(1);
                return;
            }

            QList<QHostAddress> addresses = host.addresses();
            for (const QHostAddress &address : addresses)
                err << "Found address: " << address.toString() << "\n";
            assert(!addresses.empty());

            if (!client.sendRequest(addresses[0], 123)) {
               err << "Failed to send NTP request: " << client.socket()->errorString() << "\n";
               loop.exit(1);
            }
        });
    });

    return loop.exec();
}
