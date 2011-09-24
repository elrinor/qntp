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
#ifndef QNTP_PACKET_H
#define QNTP_PACKET_H

#include "config.h"
#include <QtGlobal>
#include "QNtp.h"
#include "NtpTimestamp.h"

/**
 * NtpPacket flags (first byte of the packet).
 */
struct NtpPacketFlags {
  /** Mode. */
  unsigned char mode: 3;

  /** Version number of the protocol (3 or 4). */
  unsigned char versionNumber: 3;

  /** Warns of an impending leap second to be inserted/deleted in the last minute 
   * of the current day. */
  unsigned char leapIndicator: 2;
};

#pragma pack(push, 1)
/**
 * Mandatory part of an NTP packet
 */
struct NtpPacket {
  /** Flags. */
  NtpPacketFlags flags;

  /** Stratum of the clock. */
  quint8 stratum;

  /** Maximum interval between successive messages, in log2 seconds. Note that the value is signed. */
  qint8 poll;

  /** Precision of the clock, in log2 seconds. Note that the value is signed. */
  qint8 precision;

  /** Round trip time to the primary reference source, in NTP short format. */
  qint32 rootDelay;

  /** Nominal error relative to the primary reference source. */
  qint32 rootDispersion;

  /** Reference identifier (either a 4 character string or an IP address). */
  qint8 referenceID[4];

  /** The time at which the clock was last set or corrected. */
  NtpTimestamp referenceTimestamp;

  /** The time at which the request departed the client for the server. */
  NtpTimestamp originateTimestamp;

  /** The time at which the request arrived at the server. */
  NtpTimestamp receiveTimestamp;

  /** The time at which the reply departed the server for client. */
  NtpTimestamp transmitTimestamp;
};

/**
 * Optional part of an NTP packet.
 */
struct NtpAuthenticationInfo {
  /** Key identifier. */
  quint32 keyId;

  /** Message Digest. */
  quint8 messageDigest[16];
};

/**
 * Full NTP packet.
 */
struct NtpFullPacket {
  NtpPacket basic;
  NtpAuthenticationInfo auth;
};
#pragma pack(pop)


#endif // QNTP_PACKET_H
