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
        m_serviceType(EmailServiceProviderInfo::SENDMAIL), m_tls(false),
        m_tlsRequired(false), m_authenticationType(EmailServiceProviderInfo::AuthNone)
    {
    }

    EmailServiceProviderInfoPrivate(const EmailServiceProviderInfoPrivate& d)
    {
        *this = d;
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
        std::swap(m_serviceType, d.m_serviceType);
        std::swap(m_tls, d.m_tls);
        std::swap(m_tlsRequired, d.m_tlsRequired);
        m_rootPath.swap(d.m_rootPath);
        m_sendmailPath.swap(d.m_sendmailPath);
        std::swap(m_authenticationType, d.m_authenticationType);
    }

    EmailServiceProviderInfo::ServiceType m_serviceType;
    bool m_tls;
    bool m_tlsRequired;
    QString m_rootPath;
    QString m_sendmailPath;
    int m_authenticationType;
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
    *this = providerInfo;
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

EmailServiceProviderInfo::ServiceType EmailServiceProviderInfo::serviceType() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_serviceType;
}

void EmailServiceProviderInfo::setServiceType(ServiceType serviceType)
{
    Q_D(EmailServiceProviderInfo);
    d->m_serviceType = serviceType;
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

bool EmailServiceProviderInfo::authenication() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authenticationType != AuthNone;
}

bool EmailServiceProviderInfo::apop() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authenticationType & AuthAPOP;
}

bool EmailServiceProviderInfo::apopFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authenticationType & ~AuthAPOP) != AuthAPOP;
}

bool EmailServiceProviderInfo::cleartext() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authenticationType & AuthCleartext;
}

bool EmailServiceProviderInfo::cleartextFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authenticationType & ~AuthCleartext) != AuthCleartext;
}

bool EmailServiceProviderInfo::plain() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authenticationType & AuthPlain;
}

bool EmailServiceProviderInfo::plainFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authenticationType & ~AuthPlain) != AuthPlain;
}

bool EmailServiceProviderInfo::sasl() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_authenticationType & AuthSASL;
}

bool EmailServiceProviderInfo::saslFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return (d->m_authenticationType & ~AuthSASL) != AuthSASL;
}

bool EmailServiceProviderInfo::smtpAuthentication() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_serviceType == SMTP && d->m_authenticationType != AuthNone;
}


} // namespace Services
} // namespace Maily
