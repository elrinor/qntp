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
#ifndef QNTP_QNTP_H
#define QNTP_QNTP_H

#include "config.h"

/**
 * Leap indicators.
 */ 
enum NtpLeapIndicator {
  NoWarning = 0,             /**< No warning. */
  LastMinute61Warning = 1,   /**< Last minute has 61 seconds. */
  LastMinute59Warning = 2,   /**< Last minute has 59 seconds. */
  UnsynchronizedWarning = 3, /**< Alarm condition (clock not synchronized). */
};

/**
 * Modes.
 */
enum NtpMode {
  ReservedMode = 0,         /**< Reserved. */
  SymmetricActiveMode = 1,  /**< Symmetric active. */
  SymmetricPassiveMode = 2, /**< Symmetric passive. */
  ClientMode = 3,           /**< Client. */
  ServerMode = 4,           /**< Server. */
  BroadcastMode = 5,        /**< Broadcast. */
  ControlMode = 6,          /**< NTP control message. */
  PrivateMode = 7,          /**< Reserved for private use. */
};

/**
 * Strata.
 */
enum NtpStratum {
  UnspecifiedStratum = 0,     /**< Unspecified or unavailable. */
  PrimaryStratum = 1,         /**< Primary reference (e.g. radio-clock). */
  SecondaryStratumFirst = 2,  /**< Secondary reference (via NTP or SNTP). */
  SecondaryStratumLast = 15,
  UnsynchronizedStratum = 16, /**< Unsynchronized. */
  /* 17-255 are reserved. */
};

#endif // QNTP_QNTP_H
