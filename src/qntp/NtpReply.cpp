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
#include "NtpReply.h"
#include <cmath> /* For std::pow. */
#include "NtpReply_p.h"

NtpReply::NtpReply(): d(new NtpReplyPrivate()) {
  /* We don't use shared null because NtpReplyPrivate isn't a POD type and
   * allocation overhead is negligible here. */
  qMemSet(&d->packet, 0, sizeof(d->packet));
}

NtpReply::NtpReply(NtpReplyPrivate *dd): d(dd) {
  Q_ASSERT(dd != NULL);
}

NtpReply::NtpReply(const NtpReply &other): d(other.d) {}

NtpReply::~NtpReply() {}

NtpReply &NtpReply::operator=(const NtpReply &other) {
  d = other.d;

  return *this;
}
  
NtpLeapIndicator NtpReply::leapIndicator() const {
  return static_cast<NtpLeapIndicator>(d->packet.basic.flags.leapIndicator);
}

quint8 NtpReply::versionNumber() const {
  return d->packet.basic.flags.versionNumber;
}

NtpMode NtpReply::mode() const {
  return static_cast<NtpMode>(d->packet.basic.flags.mode);
}

quint8 NtpReply::stratum() const {
  return d->packet.basic.stratum;
}

qreal NtpReply::pollInterval() const {
  return std::pow(static_cast<qreal>(2), static_cast<qreal>(d->packet.basic.poll));
}

qreal NtpReply::precision() const {
  return std::pow(static_cast<qreal>(2), static_cast<qreal>(d->packet.basic.precision));
}

QDateTime NtpReply::referenceTime() const {
  return NtpTimestamp::toDateTime(d->packet.basic.referenceTimestamp);
}

QDateTime NtpReply::originTime() const {
  return NtpTimestamp::toDateTime(d->packet.basic.originateTimestamp);
}

QDateTime NtpReply::receiveTime() const {
  return NtpTimestamp::toDateTime(d->packet.basic.receiveTimestamp);
}

QDateTime NtpReply::transmitTime() const {
  return NtpTimestamp::toDateTime(d->packet.basic.transmitTimestamp);
}

QDateTime NtpReply::destinationTime() const {
  return d->destinationTime;
}

qint64 NtpReply::roundTripDelay() const {
  return originTime().msecsTo(destinationTime()) - receiveTime().msecsTo(transmitTime());
}

qint64 NtpReply::localClockOffset() const {
  return (originTime().msecsTo(receiveTime()) + destinationTime().msecsTo(transmitTime())) / 2;
}

bool NtpReply::isNull() const {
  return d->destinationTime.isNull();
}
