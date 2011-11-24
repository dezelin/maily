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

#include "serviceproviderinfo.h"

namespace Maily
{
namespace Services
{

class ServiceProviderInfoPrivate
{
public:
    ServiceProviderInfoPrivate() :
        m_port(0)
    {
    }

    ServiceProviderInfoPrivate(const ServiceProviderInfoPrivate& d) :
        m_address(d.m_address), m_port(d.m_port), m_displayName(d.m_displayName),
        m_displayShortName(d.m_displayShortName)
    {
    }

    ServiceProviderInfoPrivate& operator =(const ServiceProviderInfoPrivate& d)
    {
        if (this == &d)
            return *this;

        ServiceProviderInfoPrivate tmp(d);
        swap(tmp);
        return *this;
    }

    const ServiceProviderInfoPrivate&
    operator =(const ServiceProviderInfoPrivate& d) const
    {
        return (*this = d);
    }

    void swap(ServiceProviderInfoPrivate& d)
    {
        m_address.swap(d.m_address);
        std::swap(m_port, d.m_port);
        m_displayName.swap(d.m_displayName);
        m_displayShortName.swap(d.m_displayShortName);
    }

    QString m_address;
    unsigned int m_port;
    QString m_displayName;
    QString m_displayShortName;
};

ServiceProviderInfo::ServiceProviderInfo()
    : LoginInfo(), d_ptr(new ServiceProviderInfoPrivate())
{
}

ServiceProviderInfo::~ServiceProviderInfo()
{
}

ServiceProviderInfo::ServiceProviderInfo(const ServiceProviderInfo& providerInfo)
: LoginInfo(providerInfo)
{
    Q_ASSERT(providerInfo.d_ptr);
    QScopedPointer<ServiceProviderInfoPrivate> tmp(
        new ServiceProviderInfoPrivate(*providerInfo.d_ptr));
    d_ptr.swap(tmp);
}

ServiceProviderInfo&
ServiceProviderInfo::operator=(const ServiceProviderInfo& providerInfo)
{
    if (this == & providerInfo)
        return *this;

    ServiceProviderInfo tmp(providerInfo);
    swap(tmp);
    return *this;
}

const ServiceProviderInfo&
ServiceProviderInfo::operator=(const ServiceProviderInfo& providerInfo) const
{
    return (*this = providerInfo);
}

void ServiceProviderInfo::swap(ServiceProviderInfo& providerInfo)
{
    d_ptr.swap(providerInfo.d_ptr);
}

const QString& ServiceProviderInfo::address() const
{
    Q_D(const ServiceProviderInfo);
    return d->m_address;
}

void ServiceProviderInfo::setAddress(const QString& address)
{
    Q_D(ServiceProviderInfo);
    d->m_address = address;
}

unsigned int ServiceProviderInfo::port() const
{
    Q_D(const ServiceProviderInfo);
    return d->m_port;
}

void ServiceProviderInfo::setPort(unsigned int port)
{
    Q_D(ServiceProviderInfo);
    d->m_port = port;
}

const QString& ServiceProviderInfo::displayName() const
{
    Q_D(const ServiceProviderInfo);
    return d->m_displayName;
}

void ServiceProviderInfo::setDisplayName(const QString& displayName)
{
    Q_D(ServiceProviderInfo);
    d->m_displayName = displayName;
}

const QString& ServiceProviderInfo::displayShortName() const
{
    Q_D(const ServiceProviderInfo);
    return d->m_displayShortName;
}

void ServiceProviderInfo::setDisplayShortName(const QString& displayShortName)
{
    Q_D(ServiceProviderInfo);
    d->m_displayShortName = displayShortName;
}


} // namespace Services
} // namespace Maily
