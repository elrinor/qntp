QT += network

DEPENDPATH += $$PWD/include

INCLUDEPATH += $$PWD/include

HEADERS += \
  $$PWD/src/qntp/Client.h \
  $$PWD/src/qntp/config.h \
  $$PWD/src/qntp/Packet.h \
  $$PWD/src/qntp/QNtp.h \
  $$PWD/src/qntp/Reply.h \
  $$PWD/src/qntp/Reply_p.h \
  $$PWD/src/qntp/Timestamp.h \

SOURCES += \
  $$PWD/src/qntp/Client.cpp \
  $$PWD/src/qntp/Reply.cpp \

DEFINES += "QNTP_EXPORT="
