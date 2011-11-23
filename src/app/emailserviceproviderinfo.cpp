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
        m_serviceType(EmailServiceProviderInfo::SENDMAIL), m_sasl(false),
        m_saslFallback(false), m_tls(false), m_tlsRequired(false),
        m_apop(false), m_apopFallback(false)
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
        std::swap(m_sasl, d.m_sasl);
        std::swap(m_saslFallback, d.m_saslFallback);
        std::swap(m_tls, d.m_tls);
        std::swap(m_tlsRequired, d.m_tlsRequired);
        m_rootPath.swap(d.m_rootPath);
        std::swap(m_apop, d.m_apop);
        std::swap(m_apopFallback, d.m_apopFallback);
    }

    EmailServiceProviderInfo::ServiceType m_serviceType;
    bool m_sasl;
    bool m_saslFallback;
    bool m_tls;
    bool m_tlsRequired;
    QString m_rootPath;
    bool m_apop;
    bool m_apopFallback;
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

bool EmailServiceProviderInfo::sasl() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_sasl;
}

void EmailServiceProviderInfo::setSasl(bool sasl)
{
    Q_D(EmailServiceProviderInfo);
    d->m_sasl = sasl;
}

bool EmailServiceProviderInfo::saslFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_saslFallback;
}

void EmailServiceProviderInfo::setSaslFallback(bool saslFallback)
{
    Q_D(EmailServiceProviderInfo);
    d->m_saslFallback = saslFallback;
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

bool EmailServiceProviderInfo::apop() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_apop;
}

void EmailServiceProviderInfo::setApop(bool apop)
{
    Q_D(EmailServiceProviderInfo);
    d->m_apop = apop;
}

bool EmailServiceProviderInfo::apopFallback() const
{
    Q_D(const EmailServiceProviderInfo);
    return d->m_apopFallback;
}

void EmailServiceProviderInfo::setApopFallback(bool apopFallback)
{
    Q_D(EmailServiceProviderInfo);
    d->m_apopFallback = apopFallback;
}

} // namespace Services
} // namespace Maily
