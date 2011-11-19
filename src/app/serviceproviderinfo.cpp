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

namespace Details
{
    struct ServiceProviderInfoPrivate
    {
        ServiceProviderInfoPrivate() :
            m_port(0)
        {

        }

        QString m_address;
        unsigned int m_port;
    };
}

ServiceProviderInfo::ServiceProviderInfo(QObject* parent)
    : LoginInfo(parent), m_data(new Details::ServiceProviderInfoPrivate())
{
}

const QString& ServiceProviderInfo::address() const
{
    Q_ASSERT(m_data);
    return m_data->m_address;
}

void ServiceProviderInfo::setAddress(const QString& address)
{
    Q_ASSERT(m_data);
    m_data->m_address = address;
}

unsigned int ServiceProviderInfo::port() const
{
    Q_ASSERT(m_data);
    return m_data->m_port;
}

void ServiceProviderInfo::setPort(unsigned int port)
{
    Q_ASSERT(m_data);
    m_data->m_port = port;
}

} // namespace Services
} // namespace Maily
