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

namespace Details
{
    struct EmailServiceProviderInfoPrivate
    {
        EmailServiceProviderInfoPrivate() :
            m_serviceType(EmailServiceProviderInfo::SENDMAIL), m_sasl(false),
            m_saslFallback(false), m_tls(false), m_tlsRequired(false),
            m_apop(false), m_apopFallback(false)
        {

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
}

EmailServiceProviderInfo::EmailServiceProviderInfo(QObject *parent) :
    ServiceProviderInfo(parent),
    m_data(new Details::EmailServiceProviderInfoPrivate())
{
}

EmailServiceProviderInfo::ServiceType EmailServiceProviderInfo::serviceType() const
{
    Q_ASSERT(m_data);
    return m_data->m_serviceType;
}

void EmailServiceProviderInfo::setServiceType(ServiceType serviceType)
{
    Q_ASSERT(m_data);
    m_data->m_serviceType = serviceType;
}

bool EmailServiceProviderInfo::sasl() const
{
    Q_ASSERT(m_data);
    return m_data->m_sasl;
}

void EmailServiceProviderInfo::setSasl(bool sasl)
{
    Q_ASSERT(m_data);
    m_data->m_sasl = sasl;
}

bool EmailServiceProviderInfo::saslFallback() const
{
    Q_ASSERT(m_data);
    return m_data->m_saslFallback;
}

void EmailServiceProviderInfo::setSaslFallback(bool saslFallback)
{
    Q_ASSERT(m_data);
    m_data->m_saslFallback = saslFallback;
}

bool EmailServiceProviderInfo::tls() const
{
    Q_ASSERT(m_data);
    return m_data->m_tls;
}

void EmailServiceProviderInfo::setTls(bool tls)
{
    Q_ASSERT(m_data);
    m_data->m_tls = tls;
}

bool EmailServiceProviderInfo::tlsRequired() const
{
    Q_ASSERT(m_data);
    return m_data->m_tlsRequired;
}

void EmailServiceProviderInfo::setTlsRequired(bool tlsRequired)
{
    Q_ASSERT(m_data);
    m_data->m_tlsRequired = tlsRequired;
}

const QString& EmailServiceProviderInfo::rootPath() const
{
    Q_ASSERT(m_data);
    return m_data->m_rootPath;
}

void EmailServiceProviderInfo::setRootPath(const QString& rootPath)
{
    Q_ASSERT(m_data);
    m_data->m_rootPath = rootPath;
}

bool EmailServiceProviderInfo::apop() const
{
    Q_ASSERT(m_data);
    return m_data->m_apop;
}

void EmailServiceProviderInfo::setApop(bool apop)
{
    Q_ASSERT(m_data);
    m_data->m_apop = apop;
}

bool EmailServiceProviderInfo::apopFallback() const
{
    Q_ASSERT(m_data);
    return m_data->m_apopFallback;
}

void EmailServiceProviderInfo::setApopFallback(bool apopFallback)
{
    Q_ASSERT(m_data);
    m_data->m_apopFallback = apopFallback;
}

} // namespace Services
} // namespace Maily
