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
    servicestoolbox.cpp \
    emailaccountstreeview.cpp \
    calendaraccountstreeview.cpp \
    emailaccountssqlquerymodel.cpp \
    calendaraccountssqlquerymodel.cpp

HEADERS  += mainwindow.h \
    servicestoolbox.h \
    emailaccountstreeview.h \
    calendaraccountstreeview.h \
    emailaccountssqlquerymodel.h \
    calendaraccountssqlquerymodel.h

FORMS    += mainwindow.ui
