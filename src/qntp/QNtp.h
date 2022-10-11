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
