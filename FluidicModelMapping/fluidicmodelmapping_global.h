#ifndef FLUIDICMODELMAPPING_GLOBAL_H
#define FLUIDICMODELMAPPING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FLUIDICMODELMAPPING_LIBRARY)
#  define FLUIDICMODELMAPPINGSHARED_EXPORT Q_DECL_EXPORT
#  define MACHINEFLOWSTRINGADAPTER_EXPORT Q_DECL_EXPORT
#  define ASTARSEARCH_EXPORT Q_DECL_EXPORT
#  define TOPOLOGYHEURISTIC_EXPORT Q_DECL_EXPORT
#  define CONTAINERCHARACTERISTICS_EXPORT Q_DECL_EXPORT
#  define ANALYSISEXECUTOR_EXPORT Q_DECL_EXPORT
#else
#  define FLUIDICMODELMAPPINGSHARED_EXPORT Q_DECL_IMPORT
#  define MACHINEFLOWSTRINGADAPTER_EXPORT Q_DECL_IMPORT
#  define ASTARSEARCH_EXPORT Q_DECL_IMPORT
#  define TOPOLOGYHEURISTIC_EXPORT Q_DECL_IMPORT
#  define CONTAINERCHARACTERISTICS_EXPORT Q_DECL_IMPORT
#  define ANALYSISEXECUTOR_EXPORT Q_DECL_IMPORT
#endif

#endif // FLUIDICMODELMAPPING_GLOBAL_H
