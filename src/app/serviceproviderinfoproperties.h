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

#ifndef SERVICEPROVIDERINFOPROPERTIES_H
#define SERVICEPROVIDERINFOPROPERTIES_H

#include "serviceproviderinfo.h"

#include <QMap>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{

class ServiceProviderInfoPropertiesPrivate;
class ServiceProviderInfoProperties
{
public:
    ServiceProviderInfoProperties(const ServiceProviderInfo* info = 0);
    virtual ~ServiceProviderInfoProperties();

    ServiceProviderInfoProperties(
        const ServiceProviderInfoProperties& properties);

    ServiceProviderInfoProperties& operator =(
        const ServiceProviderInfoProperties& properties);

    const ServiceProviderInfoProperties& operator =(
        const ServiceProviderInfoProperties& properties) const;

    void swap(ServiceProviderInfoProperties& properties);

    static QMap<QString, QString>* create(const ServiceProviderInfo* info) const;

    const QString& get(const QString& name) const;
    void set(const QString& name, const QString& value);

private:
    Q_DECLARE_PRIVATE(ServiceProviderInfoProperties)
    QScopedPointer<ServiceProviderInfoPropertiesPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // SERVICEPROVIDERINFOPROPERTIES_H
