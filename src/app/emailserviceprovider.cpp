/*
 *   This file is part of Maily.
 *
 *   Maily is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Maily is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Maily. If not, see <http://www.gnu.org/licenses/>.
 */

#include <vmime/vmime.hpp>

#include "dummycertverifier.h"
#include "emailserviceprovider.h"
#include "emailserviceproviderinfo.h"
#include "tools.h"

namespace Maily
{
namespace Services
{

static vmime::ref<vmime::net::session> createSingleSession(
    const EmailServiceProviderInfo& info,
    EmailServiceProviderInfo::ServiceTypes serviceType)
{
    QString prefix;
    QString protocol;
    if (serviceType == EmailServiceProviderInfo::POP3) {
        prefix = "store";
        protocol = "pop3";
    } else if (serviceType == EmailServiceProviderInfo::POP3S) {
        prefix = "store";
        protocol = "pop3s";
    } else if (serviceType == EmailServiceProviderInfo::IMAP) {
        prefix = "store";
        protocol = "imap";
    } else if (serviceType == EmailServiceProviderInfo::IMAPS) {
        prefix = "store";
        protocol = "imaps";
    } else if (serviceType == EmailServiceProviderInfo::MAILDIR) {
        prefix = "store";
        protocol = "maildir";
    } else if (serviceType == EmailServiceProviderInfo::SMTP) {
        prefix = "transport";
        protocol = "smtp";
    } else if (serviceType == EmailServiceProviderInfo::SMTPS) {
        prefix = "transport";
        protocol = "smtps";
    } else {
        prefix = "transport";
        protocol = "sendmail";
    }

    prefix += "." + protocol + ".";

    vmime::ref<vmime::net::session> session =
        vmime::create<vmime::net::session>();
    vmime::propertySet& p = session->getProperties();

    p["store.protocol"] = protocol.toStdString();

    if (serviceType == EmailServiceProviderInfo::POP3
        || serviceType == EmailServiceProviderInfo::POP3S
        || serviceType == EmailServiceProviderInfo::IMAP
        || serviceType == EmailServiceProviderInfo::IMAPS
        || serviceType == EmailServiceProviderInfo::SMTP
        || serviceType == EmailServiceProviderInfo::SMTPS)
    {
        p[QString(prefix + "options.sasl").toStdString()] =
            info.sasl() ? "true" : "false";
        p[QString(prefix + "options.sasl.fallback").toStdString()] =
            info.saslFallback() ? "true" : "false";
        p[QString(prefix + "auth.username").toStdString()] =
            info.username().toStdString();
        p[QString(prefix + "auth.password").toStdString()] =
            info.password().toStdString();
        p[QString(prefix + "server.address").toStdString()] =
            info.address().toStdString();
        int port = info.port();
        if (port != 0) {
            p[QString(prefix + "server.port").toStdString()] =
                QString("%1").arg(info.port()).toStdString();
        }
    }

    if (serviceType == EmailServiceProviderInfo::POP3
        || serviceType == EmailServiceProviderInfo::IMAP
        || serviceType == EmailServiceProviderInfo::SMTP)
    {
        p[QString(prefix + "connection.tls").toStdString()] =
            info.tls() ? "true" : "false";
        p[QString(prefix + "connection.tls.required").toStdString()] =
            info.tlsRequired() ? "true" : "false";
    }

    if (serviceType == EmailServiceProviderInfo::MAILDIR) {
        p[QString(prefix + "server.rootpath").toStdString()] =
            info.rootPath().toStdString();
    }

    if (serviceType == EmailServiceProviderInfo::POP3
        || serviceType == EmailServiceProviderInfo::POP3S)
    {
        p[QString(prefix + "options.apop").toStdString()] =
            info.apop() ? "true" : "false";
        p[QString(prefix + "options.apop.fallback").toStdString()] =
            info.apopFallback() ? "true" : "false";
    }

    if (serviceType == EmailServiceProviderInfo::SMTP
        || serviceType == EmailServiceProviderInfo::SMTPS)
    {
        p[QString(prefix + "options.need-authentication").toStdString()] =
            info.smtpAuthentication() ? "true" : "false";
    }

    if (serviceType == EmailServiceProviderInfo::SENDMAIL) {
        p[QString(prefix + "binpath").toStdString()] =
            info.sendmailBinPath().toStdString();
    }

    return session;
}

static QList<vmime::ref<vmime::net::session> >* createSessionList(
    const EmailServiceProviderInfo& info)
{
    QScopedPointer<QList<vmime::ref<vmime::net::session> > > list(
        new QList<vmime::ref<vmime::net::session> >());

    vmime::ref<vmime::net::session> session;
    EmailServiceProviderInfo::ServiceTypes type = info.serviceType();
    if (type & EmailServiceProviderInfo::IMAPS) {
        session = createSingleSession(info, EmailServiceProviderInfo::IMAPS);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::IMAP) {
        session = createSingleSession(info, EmailServiceProviderInfo::IMAP);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::POP3S) {
        session = createSingleSession(info, EmailServiceProviderInfo::POP3S);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::POP3) {
        session = createSingleSession(info, EmailServiceProviderInfo::POP3);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::MAILDIR) {
        session = createSingleSession(info, EmailServiceProviderInfo::MAILDIR);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::SMTPS) {
        session = createSingleSession(info, EmailServiceProviderInfo::SMTPS);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::SMTP) {
        session = createSingleSession(info, EmailServiceProviderInfo::SMTP);
        *list << session;
    }

    if (type & EmailServiceProviderInfo::SENDMAIL) {
        session = createSingleSession(info, EmailServiceProviderInfo::SENDMAIL);
        *list << session;
    }

    return list.take();
}

void dumpToLog(vmime::ref<vmime::net::session> session)
{
    typedef std::vector<vmime::ref<vmime::propertySet::property> >
        PropertyList;
    PropertyList list = session->getProperties().getPropertyList();
    PropertyList::const_iterator end = list.end();
    for(PropertyList::const_iterator it = list.begin(); it != end; ++it) {
        qLog() << QString("%1 %2").arg(
            (*it)->getName().c_str()).arg((*it)->getValue().c_str());
    }

}

class EmailServiceProviderPrivate
{
public:
    EmailServiceProviderPrivate(EmailServiceProviderInfo* info) :
        dummyCert(false), providerInfo(info)
    {
    }

    void reset(EmailServiceProviderInfo* info)
    {
        providerInfo.reset(info);
    }

    bool dummyCert;
    vmime::ref<vmime::net::service> service;
    vmime::ref<vmime::net::session> session;
    QScopedPointer<EmailServiceProviderInfo> providerInfo;
};

EmailServiceProvider::EmailServiceProvider(QObject *parent,
    EmailServiceProviderInfo *providerInfo) :
    QObject(parent), d_ptr(new EmailServiceProviderPrivate(providerInfo))
{
}

EmailServiceProvider::~EmailServiceProvider()
{
    if (!isConnected())
        return;

    disconnect();
}

bool EmailServiceProvider::connect()
{
    Q_D(EmailServiceProvider);

    Q_ASSERT(d->providerInfo);
    if (!d->providerInfo)
        return false;

    Q_ASSERT(!d->session && !d->service);
    if (d->session || d->service)
        return false;

    QScopedPointer<QList<vmime::ref<vmime::net::session> > > sessions(
        createSessionList(*d->providerInfo));
    Q_ASSERT(sessions);
    if (!sessions)
        return false;

    vmime::ref<vmime::net::session> session;
    vmime::ref<vmime::net::service> service;
    EmailServiceProviderInfo::ServiceTypes serviceType =
        d->providerInfo->serviceType();
    for(int i = 0; i < sessions->size(); ++i) {
        vmime::ref<vmime::net::session> currentSession = sessions->at(i);

        dumpToLog(currentSession);

        if (serviceType == EmailServiceProviderInfo::SMTP
            || serviceType == EmailServiceProviderInfo::SMTPS
            || serviceType == EmailServiceProviderInfo::SENDMAIL)
        {
            // transports
            try {
                vmime::ref<vmime::net::transport> transport =
                    currentSession->getTransport();
                if (d->dummyCert)
                    transport->setCertificateVerifier(
                        vmime::create<Security::DummyCertVerifier>());

                transport->connect();
                session = currentSession;
                service = transport;

                // break the for loop
                break;

            } catch (vmime::exception& e) {
                qLog() << e.what();
            }
        } else {
            // stores
            try {
                vmime::ref<vmime::net::store> store =
                    currentSession->getStore();
                if (d->dummyCert)
                    store->setCertificateVerifier(
                        vmime::create<Security::DummyCertVerifier>());

                store->connect();
                session = currentSession;
                service = store;

                // break the for loop
                break;

            } catch (vmime::exception& e) {
                qLog() << e.what();
            }
        }
    }

    if (!session || !service)
        return false;

    d->session = session;
    d->service = service;
    return true;
}

bool EmailServiceProvider::disconnect()
{
    Q_D(EmailServiceProvider);

    Q_ASSERT(d->session && d->service);
    if (!d->session || !d->service)
        return false;

    bool disconnected = false;

    try {
        d->service->disconnect();
        disconnected = true;
        d->session = 0;
        d->service = 0;
    } catch (vmime::exception& e) {
        qLog() << e.what();
    }

    return disconnected;
}

bool EmailServiceProvider::isConnected() const
{
    Q_D(const EmailServiceProvider);

    Q_ASSERT(d->session && d->service);
    if (!d->session || !d->service)
        return false;

    return d->service->isConnected();
}

void EmailServiceProvider::setDummyCertVerifier(bool dummy)
{
    Q_D(EmailServiceProvider);
    d->dummyCert = dummy;
}

bool EmailServiceProvider::createSession()
{
    Q_D(EmailServiceProvider);


    return d->service;
}

QString EmailServiceProvider::serviceTypeString() const
{
    Q_D(const EmailServiceProvider);

    QString serviceType;

    switch(d->providerInfo->serviceType()) {
        case EmailServiceProviderInfo::POP3: {
            serviceType = "pop3";
            break;
        }
        case EmailServiceProviderInfo::POP3S: {
            serviceType = "pop3s";
            break;
        }
        case EmailServiceProviderInfo::IMAP: {
            serviceType = "imap";
            break;
        }
        case EmailServiceProviderInfo::IMAPS: {
            serviceType = "imaps";
            break;
        }
        case EmailServiceProviderInfo::SMTP: {
            serviceType = "smtp";
            break;
        }
        case EmailServiceProviderInfo::SMTPS: {
            serviceType = "smtps";
            break;
        }
        case EmailServiceProviderInfo::MAILDIR: {
            serviceType = "maildir";
            break;
        }
        case EmailServiceProviderInfo::SENDMAIL: {
            serviceType = "sendmail";
            break;
        }
        default: {
            qFatalAssert(!"Unknown service type");
        }
    }

    return serviceType;
}

} // namespace Services
} // namespace Maily

