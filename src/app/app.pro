#-------------------------------------------------
#
# Project created by QtCreator 2011-09-07T14:08:15
#
#-------------------------------------------------

QT       += core declarative gui network sql webkit

TARGET = maily
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    servicestoolbox.cpp \
    emailaccountstreeview.cpp \
    calendaraccountstreeview.cpp \
    emailaccountssqlquerymodel.cpp \
    calendaraccountssqlquerymodel.cpp \
    busyindicator.cpp \
    busyindicatorwidget.cpp \
    emailaccountwizard.cpp

HEADERS  += mainwindow.h \
    servicestoolbox.h \
    emailaccountstreeview.h \
    calendaraccountstreeview.h \
    emailaccountssqlquerymodel.h \
    calendaraccountssqlquerymodel.h \
    busyindicator.h \
    busyindicatorwidget.h \
    emailaccountwizard.h

FORMS    += mainwindow.ui
