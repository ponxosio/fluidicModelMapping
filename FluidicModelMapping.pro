#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T13:20:04
#
#-------------------------------------------------

QT       -= gui

TARGET = FluidicModelMapping
TEMPLATE = lib

DEFINES += FLUIDICMODELMAPPING_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    fluidicmodelmapping/fluidicmodelmapping_global.h \
    fluidicmodelmapping/fluidicmodelmapping.h \
    fluidicmodelmapping/fluidicmachineconnectiontable.h \
    fluidicmodelmapping/heuristic/heuristicinterface.h \
    fluidicmodelmapping/heuristic/topographyheuristic.h \
    fluidicmodelmapping/heuristic/deepsearch.h \
    fluidicmodelmapping/protocolAnalysis/analysisexecutor.h \
    fluidicmodelmapping/protocolAnalysis/containercharacteristicsexecutor.h \
    fluidicmodelmapping/heuristic/containercharacteristics.h \
    fluidicmodelmapping/protocolAnalysis/machineflowstringadapter.h

debug {
    QMAKE_POST_LINK=X:\fluidicModelMapping\fluidicModelMapping\setDLL.bat $$shell_path($$OUT_PWD/debug) debug

    INCLUDEPATH += X:\fluidicMachineModel\dll_debug\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_debug\bin) -lFluidicMachineModel

    INCLUDEPATH += X:\utils\dll_debug\include
    LIBS += -L$$quote(X:\utils\dll_debug\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_debug\include
    LIBS += -L$$quote(X:\commomModel\dll_debug\bin) -lcommonModel

    INCLUDEPATH += X:\protocolGraph\dll_debug\include
    LIBS += -L$$quote(X:\protocolGraph\dll_debug\bin) -lprotocolGraph
}

!debug {
    QMAKE_POST_LINK=X:\fluidicModelMapping\fluidicModelMapping\setDLL.bat $$shell_path($$OUT_PWD/release) release

    INCLUDEPATH += X:\fluidicMachineModel\dll_release\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_release\bin) -lFluidicMachineModel

    INCLUDEPATH += X:\utils\dll_release\include
    LIBS += -L$$quote(X:\utils\dll_release\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_release\include
    LIBS += -L$$quote(X:\commomModel\dll_release\bin) -lcommonModel

    INCLUDEPATH += X:\protocolGraph\dll_release\include
    LIBS += -L$$quote(X:\protocolGraph\dll_release\bin) -lprotocolGraph
}

INCLUDEPATH += X:\libraries\cereal-1.2.2\include

INCLUDEPATH += X:\swipl\include
LIBS += -L$$quote(X:\swipl\bin) -llibswipl
LIBS += -L$$quote(X:\swipl\lib) -llibswipl

SOURCES += \
    fluidicmodelmapping/fluidicmodelmapping.cpp \
    fluidicmodelmapping/fluidicmachineconnectiontable.cpp \
    fluidicmodelmapping/heuristic/topographyheuristic.cpp \
    fluidicmodelmapping/heuristic/deepsearch.cpp \
    fluidicmodelmapping/protocolAnalysis/analysisexecutor.cpp \
    fluidicmodelmapping/protocolAnalysis/containercharacteristicsexecutor.cpp \
    fluidicmodelmapping/heuristic/containercharacteristics.cpp \
    fluidicmodelmapping/protocolAnalysis/machineflowstringadapter.cpp
