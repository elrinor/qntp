TEMPLATE = lib
TARGET   = qntp
QT      -= gui
QT      += network

MOC_DIR = temp/moc

INCLUDEPATH += \
  include \

CONFIG(debug, debug|release) {
  DESTDIR         = debug
  OBJECTS_DIR     = debug
}

CONFIG(release, debug|release) {
  DESTDIR         = release
  OBJECTS_DIR     = release
}

DEFINES += QNTP_BUILDING

HEADERS += \
  src/qntp/Client.h \
  src/qntp/config.h \
  src/qntp/Packet.h \
  src/qntp/QNtp.h \
  src/qntp/Reply.h \
  src/qntp/Reply_p.h \
  src/qntp/Timestamp.h \

SOURCES += \
  src/qntp/Client.cpp \
  src/qntp/Reply.cpp \
