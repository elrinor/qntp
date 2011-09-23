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
