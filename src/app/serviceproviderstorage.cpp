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

#include "serviceproviderstorage.h"
#include "store.h"

namespace Maily
{
namespace Services
{
namespace Storage
{

class ServiceProviderStoragePrivate
{
public:
    ServiceProviderStoragePrivate(Store *m, Store *a) :
        meta(m), account(a)
    {
    }

    QScopedPointer<Store> meta;
    QScopedPointer<Store> account;
};

ServiceProviderStorage::ServiceProviderStorage(QObject *parent, Store *meta,
    Store *account) :
    QObject(parent),
    d_ptr(new ServiceProviderStoragePrivate(meta, account))
{
}

ServiceProviderStorage::~ServiceProviderStorage()
{
}

bool ServiceProviderStorage::close()
{
}

bool ServiceProviderStorage::open()
{
}

bool ServiceProviderStorage::remove()
{
}

bool ServiceProviderStorage::upgrade()
{
}

int ServiceProviderStorage::version() const
{
    Q_D(const ServiceProviderStorage);
    return d->meta->version();
}

ServiceProviderInfo *ServiceProviderStorage::getProviderInfo() const
{
}

bool ServiceProviderStorage::isOpened() const
{
    Q_D(const ServiceProviderStorage);
    return d->meta->isOpened() && d->account->isOpened();
}

} // namespace Storage
} // namespace Services
} // namespace Maily
