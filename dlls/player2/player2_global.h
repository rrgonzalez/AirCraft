#ifndef PLAYER2_GLOBAL_H
#define PLAYER2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLAYER2_LIBRARY)
#  define PLAYER2SHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLAYER2SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLAYER2_GLOBAL_H
