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

#ifndef SERVICEPROVIDERINFO_H
#define SERVICEPROVIDERINFO_H

#include <QScopedPointer>

#include "logininfo.h"

namespace Maily
{
namespace Services
{

class ServiceProviderInfoPrivate;
class ServiceProviderInfo : public LoginInfo
{
public:
    ServiceProviderInfo();
    virtual ~ServiceProviderInfo();

    ServiceProviderInfo(const ServiceProviderInfo& providerInfo);
    ServiceProviderInfo& operator=(const ServiceProviderInfo& providerInfo);
    const ServiceProviderInfo& operator=(const ServiceProviderInfo& providerInfo) const;

    void swap(ServiceProviderInfo& providerInfo);

    const QString& address() const;
    void setAddress(const QString& address);

    unsigned int port() const;
    void setPort(unsigned int port);

    const QString& displayName() const;
    void setDisplayName(const QString& displayName);

    const QString& displayShortName() const;
    void setDisplayShortName(const QString& displayShortName);

private:
    Q_DECLARE_PRIVATE(ServiceProviderInfo)
    QScopedPointer<ServiceProviderInfoPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // SERVICEPROVIDERINFO_H
