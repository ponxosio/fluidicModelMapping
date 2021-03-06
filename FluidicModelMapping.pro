#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T13:20:04
#
#-------------------------------------------------

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}
    # ensure one "debug" or "release" in CONFIG so they can be used as
    #   conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

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
    fluidicmodelmapping/heuristic/heuristicinterface.h \
    fluidicmodelmapping/protocolAnalysis/analysisexecutor.h \
    fluidicmodelmapping/protocolAnalysis/containercharacteristicsexecutor.h \
    fluidicmodelmapping/heuristic/containercharacteristics.h \
    fluidicmodelmapping/searchalgorithms/deepsearch.h \
    fluidicmodelmapping/searchalgorithms/searchnode.h \
    fluidicmodelmapping/heuristic/topologyheuristic.h \
    fluidicmodelmapping/searchalgorithms/astarsearch.h \
    fluidicmodelmapping/searchalgorithms/searchinterface.h \
    fluidicmodelmapping/searchalgorithms/solutioncheck.h \
    fluidicmodelmapping/protocolAnalysis/workingrangemanager.h

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

    INCLUDEPATH += X:\bioblocksTranslation\dll_debug\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_debug\bin) -lbioblocksTranslation
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

    INCLUDEPATH += X:\bioblocksTranslation\dll_release\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_release\bin) -lbioblocksTranslation
}

INCLUDEPATH += X:\libraries\cereal-1.2.2\include
INCLUDEPATH += X:\libraries\eigen.3.3

INCLUDEPATH += X:\swipl\include
LIBS += -L$$quote(X:\swipl\bin) -llibswipl
LIBS += -L$$quote(X:\swipl\lib) -llibswipl

SOURCES += \
    fluidicmodelmapping/fluidicmodelmapping.cpp \
    fluidicmodelmapping/protocolAnalysis/analysisexecutor.cpp \
    fluidicmodelmapping/protocolAnalysis/containercharacteristicsexecutor.cpp \
    fluidicmodelmapping/heuristic/containercharacteristics.cpp \
    fluidicmodelmapping/searchalgorithms/deepsearch.cpp \
    fluidicmodelmapping/heuristic/topologyheuristic.cpp \
    fluidicmodelmapping/searchalgorithms/searchnode.cpp \
    fluidicmodelmapping/searchalgorithms/astarsearch.cpp \
    fluidicmodelmapping/searchalgorithms/solutioncheck.cpp \
    fluidicmodelmapping/protocolAnalysis/workingrangemanager.cpp
