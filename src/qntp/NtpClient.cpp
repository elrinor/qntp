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
#include "NtpClient.h"
#include <QUdpSocket>
#include <QHostAddress>
#include "NtpPacket.h"
#include "NtpReply.h"
#include "NtpReply_p.h"

NtpClient::NtpClient(QObject *parent): QObject(parent) {
  init(QHostAddress::Any, 0);
}

NtpClient::NtpClient(const QHostAddress &bindAddress, quint16 bindPort, QObject *parent): QObject(parent) {
  init(bindAddress, bindPort);
}

void NtpClient::init(const QHostAddress &bindAddress, quint16 bindPort) {
  mSocket = new QUdpSocket(this);
  mSocket->bind(bindAddress, bindPort);

  connect(mSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

NtpClient::~NtpClient() {
  return;
}

bool NtpClient::sendRequest(const QHostAddress &address, quint16 port) {
  if(mSocket->state() != QAbstractSocket::BoundState)
    return false;

  /* Initialize the NTP packet. */
  NtpPacket packet;
  qMemSet(&packet, 0, sizeof(packet));
  packet.flags.mode = ClientMode;
  packet.flags.versionNumber = 4;
  packet.transmitTimestamp = NtpTimestamp::fromDateTime(QDateTime::currentDateTimeUtc());

  /* Send it. */
  if(mSocket->writeDatagram(reinterpret_cast<const char *>(&packet), sizeof(packet), address, port) < 0)
    return false;

  return true;
}

void NtpClient::readPendingDatagrams() {
  while (mSocket->hasPendingDatagrams()) {
    NtpFullPacket packet;
    qMemSet(&packet, 0, sizeof(packet));

    QHostAddress address;
    quint16 port;

    if(mSocket->readDatagram(reinterpret_cast<char *>(&packet), sizeof(packet), &address, &port) < sizeof(NtpPacket))
      continue;

    QDateTime now = QDateTime::currentDateTime();

    /* Prepare reply. */
    NtpReplyPrivate *replyPrivate = new NtpReplyPrivate();
    replyPrivate->packet = packet;
    replyPrivate->destinationTime = now;
    NtpReply reply(replyPrivate);

    /* Notify. */
    Q_EMIT replyReceived(address, port, reply);
  }  
}

