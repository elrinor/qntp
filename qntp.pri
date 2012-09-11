QT += network

DEPENDPATH += $$PWD/include

INCLUDEPATH += $$PWD/include

HEADERS += \
  $$PWD/src/qntp/NtpClient.h \
  $$PWD/src/qntp/config.h \
  $$PWD/src/qntp/NtpPacket.h \
  $$PWD/src/qntp/QNtp.h \
  $$PWD/src/qntp/NtpReply.h \
  $$PWD/src/qntp/NtpReply_p.h \
  $$PWD/src/qntp/NtpTimestamp.h \

SOURCES += \
  $$PWD/src/qntp/NtpClient.cpp \
  $$PWD/src/qntp/NtpReply.cpp \

DEFINES += "QNTP_EXPORT="
