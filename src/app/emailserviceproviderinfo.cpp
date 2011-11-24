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

#include "emailserviceproviderinfo.h"

namespace Maily
{
namespace Services
{

struct EmailServiceProviderInfoPrivate
{
    EmailServiceProviderInfoPrivate() :
        m_tls(false), m_tlsRequired(false),
        m_serviceType(EmailServiceProviderInfo::MAILDIR),
        m_authType(EmailServiceProviderInfo::AuthNone)
    {
    }

    EmailServiceProviderInfoPrivate(const EmailServiceProviderInfoPrivate& d) :
        m_tls(d.m_tls), m_tlsRequired(d.m_tlsRequired), m_rootPath(d.m_rootPath),
        m_sendmailPath(d.m_sendmailPath),  m_serviceType(d.m_serviceType),
        m_authType(d.m_authType)
    {
    }

    EmailServiceProviderInfoPrivate&
    operator =(const EmailServiceProviderInfoPrivate& d)
    {
        if (this == &d)
            return *this;

        EmailServiceProviderInfoPrivate tmp(d);
        return *this;
    }

    const EmailServiceProviderInfoPrivate&
    operator =(const EmailServiceProviderInfoPrivate& d) const
    {
        return (*this = d);
    }

    void swap(EmailServiceProviderInfoPrivate& d)
    {
        std::swap(m_tls, d.m_tls);
        std::swap(m_tlsRequired, d.m_tlsRequired);
        m_rootPath.swap(d.m_rootPath);
        m_sendmailPath.swap(d.m_sendmailPath);
        std::swap(m_serviceType, d.m_serviceType);
        std::swap(m_authType, d.m_authType);
    }

    bool m_tls;
    bool m_tlsRequired;
    QString m_rootPath;
    QString m_sendmailPath;
    EmailServiceProviderInfo::ServiceTypes m_serviceType;
    EmailServiceProviderInfo::AuthenticationTypes m_authType;
};

EmailServiceProviderInfo::EmailServiceProviderInfo() :
    ServiceProviderInfo(), d_ptr(new EmailServiceProviderInfoPrivate())
{
}

EmailServiceProviderInfo::~EmailServiceProviderInfo()
{
}

EmailServiceProviderInfo::EmailServiceProviderInfo(
    const EmailServiceProviderInfo &providerInfo) :
        ServiceProviderInfo(providerInfo)
{
    Q_ASSERT(providerInfo.d_ptr);
    QScopedPointer<EmailServiceProviderInfoPrivate> tmp(
        new EmailServiceProviderInfoPrivate(*providerInfo.d_ptr));
    d_ptr.swap(tmp);
}

EmailServiceProviderInfo& EmailServiceProviderInfo::operator =(
    const EmailServiceProviderInfo& providerInfo)
{
    if (this == &providerInfo)
        return *this;

    EmailServiceProviderInfo tmp(providerInfo);
    swap(tmp);
    return *this;
}

const EmailServiceProviderInfo& EmailServiceProviderInfo::operator =(
    const EmailServiceProviderInfo& providerInfo) const
{
    return (*this = providerInfo);
}

void EmailServiceProviderInfo::swap(EmailServiceProviderInfo& providerInfo)
{
    d_ptr.swap(providerInfo.d_ptr);
}

EmailServiceProviderInfo::ServiceTypes EmailServiceProviderInfo::serviceType() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_serviceType;
}

void EmailServiceProviderInfo::setServiceType(ServiceTypes type)
{
    Q_D(EmailServiceProviderInfo);
    d->m_serviceType = type;
}

bool EmailServiceProviderInfo::tls() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_tls;
}

void EmailServiceProviderInfo::setTls(bool tls)
{
    Q_D(EmailServiceProviderInfo);
    d->m_tls = tls;
}

bool EmailServiceProviderInfo::tlsRequired() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_tlsRequired;
}

void EmailServiceProviderInfo::setTlsRequired(bool tlsRequired)
{
    Q_D(EmailServiceProviderInfo);
    d->m_tlsRequired = tlsRequired;
}

const QString& EmailServiceProviderInfo::rootPath() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_rootPath;
}

void EmailServiceProviderInfo::setRootPath(const QString& rootPath)
{
    Q_D(EmailServiceProviderInfo);
    d->m_rootPath = rootPath;
}

const QString& EmailServiceProviderInfo::sendmailBinPath() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_sendmailPath;
}

void EmailServiceProviderInfo::setSendmailBinPath(const QString& path)
{
    Q_D(EmailServiceProviderInfo);
    d->m_sendmailPath = path;
}

EmailServiceProviderInfo::AuthenticationTypes
EmailServiceProviderInfo::authenticationType() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authType;
}

void EmailServiceProviderInfo::setAuthenticationType(AuthenticationTypes type)
{
    Q_D(EmailServiceProviderInfo);
    d->m_authType = type;
}

bool EmailServiceProviderInfo::authenication() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authType != AuthNone;
}

bool EmailServiceProviderInfo::apop() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authType & AuthAPOP;
}

bool EmailServiceProviderInfo::apopFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authType & ~AuthAPOP) != AuthAPOP;
}

bool EmailServiceProviderInfo::cleartext() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authType & AuthCleartext;
}

bool EmailServiceProviderInfo::cleartextFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authType & ~AuthCleartext) != AuthCleartext;
}

bool EmailServiceProviderInfo::plain() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authType & AuthPlain;
}

bool EmailServiceProviderInfo::plainFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authType & ~AuthPlain) != AuthPlain;
}

bool EmailServiceProviderInfo::sasl() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authType & AuthSASL;
}

bool EmailServiceProviderInfo::saslFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authType & ~AuthSASL) != AuthSASL;
}

bool EmailServiceProviderInfo::smtpAuthentication() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_serviceType == SMTP && d->m_authType != AuthNone;
}


} // namespace Services
} // namespace Maily
