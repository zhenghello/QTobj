#ifndef IANIMAL_GLOBAL_H
#define IANIMAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IANIMAL_LIBRARY)
#  define IANIMALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IANIMALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IANIMAL_GLOBAL_H
