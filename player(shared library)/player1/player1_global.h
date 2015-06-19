#ifndef PLAYER1_GLOBAL_H
#define PLAYER1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLAYER1_LIBRARY)
#  define PLAYER1SHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLAYER1SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLAYER1_GLOBAL_H
