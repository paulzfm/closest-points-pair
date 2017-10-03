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
    core/solver.cpp \
    core/naivesolver.cpp \
    randgendialog.cpp \
    graphicsview.cpp

HEADERS  += mainwindow.h \
    core/point.h \
    core/randgen.h \
    core/solver.h \
    core/naivesolver.h \
    randgendialog.h \
    graphicsview.h \
    core/utils.h

FORMS    += mainwindow.ui \
    randgendialog.ui

CONFIG   += c++11
