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
#ifndef QNTP_NTP_REPLY_H
#define QNTP_NTP_REPLY_H

#include "config.h"
#include <QSharedDataPointer>
#include <QDateTime>
#include "QNtp.h"

class NtpReplyPrivate;

/**
 * NTP reply.
 */
class QNTP_EXPORT NtpReply {
public:
  /**
   * Default constructor. Constructs a null ntp reply.
   */
  NtpReply();

  NtpReply(const NtpReply &other);

  ~NtpReply();

  NtpReply &operator=(const NtpReply &other);

  /**
   * @returns                        Leap indicator.
   */
  NtpLeapIndicator leapIndicator() const;

  /**
   * @returns                        NTP version number.
   */
  quint8 versionNumber() const;

  /**
   * @returns                        Ntp mode.
   */
  NtpMode mode() const;

  /**
   * @returns                        Stratum.
   */
  quint8 stratum() const;

  /**
   * @returns                        Maximum interval between successive messages, in seconds.
   */
  qreal pollInterval() const;

  /**
   * @returns                        Clock precision, in seconds.
   */
  qreal precision() const;

  /**
   * @returns                        Time when the system clock was last set or corrected.
   */
  QDateTime referenceTime() const;

  /**
   * @returns                        Time at the client when the request departed for the server.
   */
  QDateTime originTime() const;

  /**
   * @returns                        Time at the server when the request arrived from the client.
   */
  QDateTime receiveTime() const;

  /**
   * @returns                        Time at the server when the response left for the client.
   */
  QDateTime transmitTime() const;

  /**
   * @returns                        Time at the client when the reply arrived from the server.
   */
  QDateTime destinationTime() const;

  /**
   * @returns                        Round trip delay, in milliseconds.
   */
  qint64 roundTripDelay() const;

  /**
   * @returns                        Local clock offset, in milliseconds.
   */
  qint64 localClockOffset() const;

  /**
   * @returns                        Whether this ntp reply is null.
   */
  bool isNull() const;

protected:
  friend class NtpClient; /* Calls protected constructor. */

  NtpReply(NtpReplyPrivate *dd);

private:
  QSharedDataPointer<NtpReplyPrivate> d;
};


#endif // QNTP_NTP_REPLY_H
