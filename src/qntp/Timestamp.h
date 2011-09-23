/* This file is part of QNtp, a library that implements NTP protocol.
 *
 * Copyright (C) 2011 Alexander Fokin <apfokin@gmail.com>
 *
 * QNtp is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * QNtp is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with QNtp. If not, see <http://www.gnu.org/licenses/>. */
#ifndef QNTP_TIME_H
#define QNTP_TIME_H

#include "config.h"
#include <QtGlobal>
#include <QtEndian>
#include <QDateTime>

namespace qntp {
  namespace detail { namespace {
    /* Number of milliseconds passed since epoch on Jan 1 1900. */
    const qint64 january_1_1900 = -2208988800000ll;
  }}

#pragma pack(push, 1)
  /**
   * 64-bit NTP timestamp.
   */
  struct Timestamp {
    /** Number of seconds passed since Jan 1 1900, in big-endian format. */
    quint32 seconds;

    /** Fractional time part, in <tt>1/0xFFFFFFFF</tt>s of a second. */
    quint32 fraction;

    /**
     * @param dateTime                 Qt date time.
     * @returns                        Ntp time for the given qt
     */
    static inline Timestamp fromDateTime(const QDateTime &dateTime);

    /**
     * @param ntpTime                  NTP timestamp.
     * @returns                        Qt date time for the given NTP timestamp.
     */
    static inline QDateTime toDateTime(const Timestamp &ntpTime);
  };
#pragma pack(pop)


  Timestamp Timestamp::fromDateTime(const QDateTime &dateTime) {
    /* Convert given time to number of milliseconds passed since Jan 1 1900. */
    qint64 ntpMSecs = dateTime.toMSecsSinceEpoch() - detail::january_1_1900;

    /* Note that NTP epoch information is lost here. Assume 1900-2036 NTP epoch. */
    quint32 seconds = ntpMSecs / 1000;
    quint32 fraction = 0x100000000ll * (ntpMSecs % 1000) / 1000;

    /* Convert to big-endian. */
    Timestamp result;
    result.seconds = qToBigEndian(seconds);
    result.fraction = qToBigEndian(fraction);
    return result;
  }

  QDateTime Timestamp::toDateTime(const Timestamp &ntpTime) {
    /* Convert to local-endian. */
    quint32 seconds = qFromBigEndian(ntpTime.seconds);
    quint32 fraction = qFromBigEndian(ntpTime.fraction);

    /* Convert NTP timestamp to number of milliseconds passed since Jan 1 1900. */ 
    qint64 ntpMSecs = seconds * 1000 + fraction * 1000ll / 0x100000000ll;

    /* Construct Qt date time. */
    return QDateTime::fromMSecsSinceEpoch(ntpMSecs + detail::january_1_1900);
  }

} // namespace qntp

#endif // QNTP_TIME_H
