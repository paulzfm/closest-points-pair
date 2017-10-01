#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T15:35:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = closest-points-pair
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core/point.cpp \
    core/randgen.cpp \
    core/solver.cpp

HEADERS  += mainwindow.h \
    core/point.h \
    utils.h \
    core/randgen.h \
    core/solver.h

FORMS    += mainwindow.ui

CONFIG   += c++11
