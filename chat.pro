######################################################################
# Automatically generated by qmake (3.0) Wed Jul 24 23:16:44 2013
######################################################################

cache() 

TEMPLATE = app
TARGET = EKChat
INCLUDEPATH += . src
RESOURCES += resources.qrc

QT += quick qml core gui declarative

# Input
SOURCES += src/chat/*.cpp src/*.cpp src/chat/net/*.cpp
HEADERS += src/chat/*.hpp src/chat/net/*.hpp
TRANSLATIONS = translations/fr.ts
OBJECTS_DIR = bin
MOC_DIR = moc

CONFIG -= app_bundle

LIBS += -lz

CONFIG += console
CONFIG += debug

QMAKE_CXXFLAGS += -Wall

macx {
    CONFIG -= app_bundle
    SPEC = macx-g++
}
