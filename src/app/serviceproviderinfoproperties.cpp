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

#include "serviceproviderinfoproperties.h"

namespace Maily
{
namespace Services
{

class ServiceProviderInfoPropertiesPrivate
{
public:
    ServiceProviderInfoPropertiesPrivate()
    {

    }

    ServiceProviderInfoPropertiesPrivate(
        const ServiceProviderInfoPropertiesPrivate& d) :
        map(d.map)
    {
    }

    ServiceProviderInfoPropertiesPrivate& operator =(
        const ServiceProviderInfoPropertiesPrivate& d)
    {
        if (this == &d)
            return *this;

        ServiceProviderInfoPropertiesPrivate tmp(d);
        swap(tmp);
        return *this;
    }

    const ServiceProviderInfoPropertiesPrivate& operator =(
        const ServiceProviderInfoPropertiesPrivate& d) const
    {
        return (*this = d);
    }

    void swap(ServiceProviderInfoPropertiesPrivate& d)
    {
        map.swap(d.map);
    }

    QScopedPointer<QMap<QString, QString> > map;
};

ServiceProviderInfoProperties::ServiceProviderInfoProperties(
    const ServiceProviderInfo* info) :
    d_ptr(new ServiceProviderInfoPropertiesPrivate())
{
}

ServiceProviderInfoProperties::~ServiceProviderInfoProperties()
{
}

ServiceProviderInfoProperties::ServiceProviderInfoProperties(
    const ServiceProviderInfoProperties& properties) :
    d_ptr(properties.d_ptr)
{
}

ServiceProviderInfoProperties& ServiceProviderInfoProperties::operator =(
    const ServiceProviderInfoProperties& properties)
{
    if (this == &properties)
        return *this;

    ServiceProviderInfoProperties tmp(properties);
    swap(tmp);
    return *this;
}

const ServiceProviderInfoProperties& ServiceProviderInfoProperties::operator =(
    const ServiceProviderInfoProperties& properties) const
{
    return (*this = properties);
}

void ServiceProviderInfoProperties::swap(ServiceProviderInfoProperties& properties)
{
    d_ptr.swap(properties.d_ptr);
}

static QMap<QString, QString>* ServiceProviderInfoProperties::create(
    const ServiceProviderInfo* info) const
{

}

const QString& ServiceProviderInfoProperties::get(const QString& name) const
{

}

void ServiceProviderInfoProperties::set(const QString& name, const QString& value)
{

}


} // namespace Services
} // namespace Maily
