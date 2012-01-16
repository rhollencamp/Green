! include( ../Common.pri ) {
		error( Could not open Common.pri )
}

QT       += core

QT       -= gui

TARGET = ../cli
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


LIBS += -L../GreenLib -lGreenLib
INCLUDEPATH += ../../Green/GreenLib
