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

#include "serviceprovideraccountstore.h"
#include "serviceproviderstorage.h"
#include "serviceprovideraccountstore-odb.hxx"
#include "tools.h"

#include <odb/database.hxx>
#include <odb/schema-catalog.hxx>
#include <exception>

namespace Maily
{
namespace Services
{
namespace Storage
{

class ServiceProviderAccountStorePrivate
{
public:
    ServiceProviderAccountStorePrivate() :
        providerInfo_(new ServiceProviderInfo())
    {
    }

    QScopedPointer<ServiceProviderInfo> providerInfo_;
};

ServiceProviderAccountStore::ServiceProviderAccountStore(QObject *parent,
    const QString &storeName, int version) :
    Store(parent, storeName, version), d_ptr(new ServiceProviderAccountStorePrivate())
{
}

ServiceProviderAccountStore::~ServiceProviderAccountStore()
{
    close();
}

bool ServiceProviderAccountStore::close()
{
    return Store::close();
}

bool ServiceProviderAccountStore::create()
{
    return Store::create();
}

bool ServiceProviderAccountStore::open()
{
    return Store::open();
}

bool ServiceProviderAccountStore::remove()
{
    return Store::remove();
}

bool ServiceProviderAccountStore::update()
{
    return Store::update();
}

ServiceProviderInfo *ServiceProviderAccountStore::getProviderInfo()
{
    Q_D(const ServiceProviderAccountStore);

    Q_ASSERT(isOpened());
    if (!isOpened())
        return 0;

    return d->providerInfo_.data();
}

void ServiceProviderAccountStore::setProviderInfo(ServiceProviderInfo *providerInfo)
{
    Q_D(ServiceProviderAccountStore);
    d->providerInfo_.reset(providerInfo);
}

odb::database *ServiceProviderAccountStore::database()
{
    ServiceProviderStorage *storage = dynamic_cast<ServiceProviderStorage*>(parent());
    Q_ASSERT(storage);
    if (!storage)
        return 0;

    return storage->database();
}

const odb::database *ServiceProviderAccountStore::database() const
{
    return database();
}

} // namespace Storage
} // namespace Services
} // namespace Maily
