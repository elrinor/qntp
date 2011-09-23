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
#include "Reply.h"
#include <cmath> /* For std::pow. */
#include "Reply_p.h"

namespace qntp {
  
  Reply::Reply(detail::ReplyPrivate *dd): d(dd) {
    Q_ASSERT(dd != NULL);
  }

  Reply::Reply(const Reply &other): d(other.d) {}

  Reply::~Reply() {}

  Reply &Reply::operator=(const Reply &other) {
    d = other.d;

    return *this;
  }
  
  LeapIndicator Reply::leapIndicator() const {
    return d->packet.basic.flags.leapIndicator;
  }

  quint8 Reply::versionNumber() const {
    return d->packet.basic.flags.versionNumber;
  }

  Mode Reply::mode() const {
    return d->packet.basic.flags.mode;
  }

  quint8 Reply::stratum() const {
    return d->packet.basic.stratum;
  }

  qreal Reply::pollInterval() const {
    return std::pow(static_cast<qreal>(2), static_cast<qreal>(d->packet.basic.poll));
  }

  qreal Reply::precision() const {
    return std::pow(static_cast<qreal>(2), static_cast<qreal>(d->packet.basic.precision));
  }

  QDateTime Reply::referenceTime() const {
    return Timestamp::toDateTime(d->packet.basic.referenceTimestamp);
  }

  QDateTime Reply::originTime() const {
    return Timestamp::toDateTime(d->packet.basic.originateTimestamp);
  }

  QDateTime Reply::receiveTime() const {
    return Timestamp::toDateTime(d->packet.basic.receiveTimestamp);
  }

  QDateTime Reply::transmitTime() const {
    return Timestamp::toDateTime(d->packet.basic.transmitTimestamp);
  }

  QDateTime Reply::destinationTime() const {
    return d->destinationTime;
  }

  uint Reply::roundTripDelay() const {
    return originTime().msecsTo(destinationTime()) - receiveTime().msecsTo(transmitTime());
  }

  uint Reply::localClockOffset() const {
    return (originTime().msecsTo(receiveTime()) + destinationTime().msecsTo(transmitTime())) / 2;
  }

} // namespace qntp
