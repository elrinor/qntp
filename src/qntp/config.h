#ifndef QNTP_CONFIG_H
#define QNTP_CONFIG_H

#include <QtGlobal>

#ifndef QNTP_EXPORT
#  if defined(QT_DLL)
#    if defined(QNTP_BUILDING)
#      define QNTP_EXPORT Q_DECL_EXPORT
#    else
#      define QNTP_EXPORT Q_DECL_IMPORT
#    endif
#  else
#    define QNTP_EXPORT
#  endif
#endif

#endif // QNTP_CONFIG_H
