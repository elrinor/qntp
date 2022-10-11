#ifndef QNTP_REPLY_P_H
#define QNTP_REPLY_P_H

#include "config.h"
#include <QSharedData>
#include "NtpPacket.h"

class NtpReplyPrivate: public QSharedData {
public:
  NtpFullPacket packet;
  QDateTime destinationTime;
};

#endif // QNTP_REPLY_P_H
