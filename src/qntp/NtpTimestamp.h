#ifndef QNTP_NTP_TIMESTAMP_H
#define QNTP_NTP_TIMESTAMP_H

#include "config.h"
#include <QtGlobal>
#include <QtEndian>
#include <QDateTime>

namespace detail { namespace {
  /* Number of milliseconds passed since epoch on Jan 1 1900. */
  const qint64 january_1_1900 = -2208988800000ll;
}}

#pragma pack(push, 1)
/**
 * 64-bit NTP timestamp.
 */
struct NtpTimestamp {
  /** Number of seconds passed since Jan 1 1900, in big-endian format. */
  quint32 seconds;

  /** Fractional time part, in <tt>1/0xFFFFFFFF</tt>s of a second. */
  quint32 fraction;

  /**
   * @param dateTime                 Qt date time.
   * @returns                        Ntp time for the given qt
   */
  static inline NtpTimestamp fromDateTime(const QDateTime &dateTime);

  /**
   * @param ntpTime                  NTP timestamp.
   * @returns                        Qt date time for the given NTP timestamp.
   */
  static inline QDateTime toDateTime(const NtpTimestamp &ntpTime);
};
#pragma pack(pop)


NtpTimestamp NtpTimestamp::fromDateTime(const QDateTime &dateTime) {
  /* Convert given time to number of milliseconds passed since Jan 1 1900. */
  qint64 ntpMSecs = dateTime.toMSecsSinceEpoch() - detail::january_1_1900;

  /* Note that NTP epoch information is lost here. Assume 1900-2036 NTP epoch. */
  quint32 seconds = ntpMSecs / 1000;
  quint32 fraction = 0x100000000ll * (ntpMSecs % 1000) / 1000;

  /* Convert to big-endian. */
  NtpTimestamp result;
  result.seconds = qToBigEndian(seconds);
  result.fraction = qToBigEndian(fraction);
  return result;
}

QDateTime NtpTimestamp::toDateTime(const NtpTimestamp &ntpTime) {
  /* Convert to local-endian. */
  quint32 seconds = qFromBigEndian(ntpTime.seconds);
  quint32 fraction = qFromBigEndian(ntpTime.fraction);

  /* Convert NTP timestamp to number of milliseconds passed since Jan 1 1900. */
  qint64 ntpMSecs = seconds * 1000ll + fraction * 1000ll / 0x100000000ll;

  /* Construct Qt date time. */
  return QDateTime::fromMSecsSinceEpoch(ntpMSecs + detail::january_1_1900);
}


#endif // QNTP_NTP_TIMESTAMP_H
