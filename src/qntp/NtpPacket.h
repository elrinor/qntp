#pragma once

#include <QtCore/QtGlobal>

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
static_assert(sizeof(NtpPacketFlags) == 1);

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
static_assert(sizeof(NtpPacket) == 48);

/**
 * Optional part of an NTP packet.
 */
struct NtpAuthenticationInfo {
    /** Key identifier. */
    quint32 keyId;

    /** Message Digest. */
    quint8 messageDigest[16];
};
static_assert(sizeof(NtpAuthenticationInfo) == 20);

/**
 * Full NTP packet.
 */
struct NtpFullPacket {
    NtpPacket basic;
    NtpAuthenticationInfo auth;
};
static_assert(sizeof(NtpFullPacket) == 68);

#pragma pack(pop)


