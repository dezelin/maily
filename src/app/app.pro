#-------------------------------------------------
#
# Project created by QtCreator 2011-09-07T14:08:15
#
#-------------------------------------------------

QT       += core declarative gui network sql webkit xml

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
    emailaccountwizard.cpp \
    logininfo.cpp \
    accountmanager.cpp \
    accountenumerator.cpp \
    mozillaaccountenumerator.cpp \
    mailyaccountenumerator.cpp \
    accountmanagerfactory.cpp \
    serviceproviderinfo.cpp \
    emailserviceproviderinfo.cpp \
    customeditline.cpp \
    emailvalidator.cpp \
    forgettablewatcher.cpp \
    tools.cpp \
    emailserviceprovider.cpp \
    serviceproviderfactory.cpp \
    emailservicetimeouthandler.cpp \
    emailservicetimeouthandlerfactory.cpp \
    serviceproviderstorage.cpp \
    emailserviceproviderstorage.cpp \
    store.cpp \
    serviceproviderstoragefactory.cpp \
    serviceproviderstoragetransaction.cpp \
    serviceprovidermetastore.cpp \
    serviceprovideraccountstore.cpp \
    emailserviceprovideraccountstore.cpp

HEADERS  += mainwindow.h \
    servicestoolbox.h \
    emailaccountstreeview.h \
    calendaraccountstreeview.h \
    emailaccountssqlquerymodel.h \
    calendaraccountssqlquerymodel.h \
    busyindicator.h \
    busyindicatorwidget.h \
    emailaccountwizard.h \
    logininfo.h \
    accountmanager.h \
    accountenumerator.h \
    mozillaaccountenumerator.h \
    mailyaccountenumerator.h \
    accountmanagerfactory.h \
    serviceproviderinfo.h \
    emailserviceproviderinfo.h \
    tools.h \
    customeditline.h \
    emailvalidator.h \
    forgettablewatcher.h \
    platform.h \
    dummycertverifier.h \
    emailserviceprovider.h \
    serviceproviderfactory.h \
    emailservicetimeouthandler.h \
    emailservicetimeouthandlerfactory.h \
    settings.h \
    serviceproviderstorage.h \
    emailserviceproviderstorage.h \
    smartlist.h \
    store.h \
    serviceproviderstoragefactory.h \
    serviceproviderstoragetransaction.h \
    serviceprovidermetastore.h \
    serviceprovideraccountstore.h \
    emailserviceprovideraccountstore.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lvmime





