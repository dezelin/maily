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
    emailaccountsqlquerymodel.cpp \
    emailaccounttreeview.cpp

HEADERS  += mainwindow.h \
    emailaccountsqlquerymodel.h \
    emailaccounttreeview.h

FORMS    += mainwindow.ui
