#pragma once

#include <cmath> /* For std::pow. */

#include <QtCore/QDateTime>

#include "NtpEnums.h"

/**
 * NTP reply.
 */
class NtpReply {
public:
    /**
     * Default constructor, constructs a null NTP reply.
     */
    NtpReply() {}

    /**
     * Constructs an NTP reply given an NTP packet and current time.
     *
     * @param packet                   NTP packet.
     * @param destinationTime          Time at the client when the reply arrived from the server.
     */
    NtpReply(NtpFullPacket packet, QDateTime destinationTime):
        m_packet(packet),
        m_destinationTime(destinationTime)
    {}

    /**
     * @returns                        Leap indicator.
     */
    NtpLeapIndicator leapIndicator() const {
        return static_cast<NtpLeapIndicator>(m_packet.basic.flags.leapIndicator);
    }

    /**
     * @returns                        NTP version number.
     */
    quint8 versionNumber() const {
        return m_packet.basic.flags.versionNumber;
    }

    /**
     * @returns                        Ntp mode.
     */
    NtpMode mode() const {
        return static_cast<NtpMode>(m_packet.basic.flags.mode);
    }

    /**
     * @returns                        Stratum.
     */
    quint8 stratum() const {
        return m_packet.basic.stratum;
    }

    /**
     * @returns                        Maximum interval between successive messages, in seconds.
     */
    qreal pollInterval() const {
        return std::pow(static_cast<qreal>(2), static_cast<qreal>(m_packet.basic.poll));
    }

    /**
     * @returns                        Clock precision, in seconds.
     */
    qreal precision() const {
        return std::pow(static_cast<qreal>(2), static_cast<qreal>(m_packet.basic.precision));
    }

    /**
     * @returns                        Time when the system clock was last set or corrected.
     */
    QDateTime referenceTime() const {
        return NtpTimestamp::toDateTime(m_packet.basic.referenceTimestamp);
    }

    /**
     * @returns                        Time at the client when the request departed for the server.
     */
    QDateTime originTime() const {
        return NtpTimestamp::toDateTime(m_packet.basic.originateTimestamp);
    }

    /**
     * @returns                        Time at the server when the request arrived from the client.
     */
    QDateTime receiveTime() const {
        return NtpTimestamp::toDateTime(m_packet.basic.receiveTimestamp);
    }

    /**
     * @returns                        Time at the server when the response left for the client.
     */
    QDateTime transmitTime() const {
        return NtpTimestamp::toDateTime(m_packet.basic.transmitTimestamp);
    }

    /**
     * @returns                        Time at the client when the reply arrived from the server.
     */
    QDateTime destinationTime() const {
        return m_destinationTime;
    }

    /**
     * @returns                        Round trip delay, in milliseconds.
     */
    qint64 roundTripDelay() const {
        return originTime().msecsTo(destinationTime()) - receiveTime().msecsTo(transmitTime());
    }

    /**
     * @returns                        Local clock offset, in milliseconds.
     */
    qint64 localClockOffset() const {
        return (originTime().msecsTo(receiveTime()) + destinationTime().msecsTo(transmitTime())) / 2;
    }

    /**
     * @return                         Raw NTP reply, for the curious user.
     */
    const NtpFullPacket &rawData() const {
        return m_packet;
    }

    /**
     * @returns                        Whether this ntp reply is null.
     */
    bool isNull() const {
        return m_destinationTime.isNull();
    }

private:
    NtpFullPacket m_packet;
    QDateTime m_destinationTime;
};


