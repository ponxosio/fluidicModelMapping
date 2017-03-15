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
    fluidicmodelmapping/fluidicmodelmapping_global.h
