#-------------------------------------------------
#
# Project created by QtCreator 2011-09-07T14:08:15
#
#-------------------------------------------------

QT       += core gui network sql webkit

TARGET = maily
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        accountmodel.cpp \
    emailaccountmodel.cpp

HEADERS  += mainwindow.h accountmodel.h \
    emailaccountmodel.h

FORMS    += mainwindow.ui
