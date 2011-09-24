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
#ifndef QNTP_NTP_CLIENT_H
#define QNTP_NTP_CLIENT_H

#include "config.h"
#include <QObject>
#include "QNtp.h"

class QUdpSocket;
class QHostAddress;

class NtpReply;

/**
 * NTP client.
 */
class QNTP_EXPORT NtpClient: public QObject {
  Q_OBJECT;
public:
  /**
   * Default constructor.
   * 
   * @param parent                   Parent of this object.
   */
  NtpClient(QObject *parent = NULL);

  /**
   * Constructor.
   * 
   * @param bindAddress              Address to bind udp socket to.
   * @param bindPort                 Port to bind udp socket to.
   * @param parent                   Parent of this object.
   */
  NtpClient(const QHostAddress &bindAddress, quint16 bindPort, QObject *parent = NULL);

  /**
   * Virtual destructor.
   */
  virtual ~NtpClient();

  /**
   * Sends NTP request.
   * 
   * @param address                  NTP server address.
   * @param port                     NTP server port.
   * @returns                        Whether the NTP request was successfully sent.
   */
  bool sendRequest(const QHostAddress &address, quint16 port);

Q_SIGNALS:
  /**
   * This signal is emitted whenever NTP reply is received.
   * 
   * @param address                  Address of the server that sent this reply.
   * @param port                     Port of the server that sent this reply.
   * @param reply                    NTP reply.
   */
  void replyReceived(const QHostAddress &address, quint16 port, const NtpReply &reply);

private Q_SLOTS:
  void readPendingDatagrams();

private:
  void init(const QHostAddress &bindAddress, quint16 bindPort);

  QUdpSocket *mSocket;
};


#endif // QNTP_NTP_CLIENT_H
