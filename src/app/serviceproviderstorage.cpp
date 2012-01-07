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
#include "storageexception.h"
#include "tools.h"

#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class ServiceProviderStoragePrivate
{
public:
    ServiceProviderStoragePrivate()
    {
    }
};

ServiceProviderStorage::ServiceProviderStorage(QObject *parent,
    ServiceProviderMetaStore *metaStore,
    ServiceProviderAccountStore *accountStore) :
    Storage(parent), d_ptr(new ServiceProviderStoragePrivate())
{
    addStore(kServiceProviderMetaStore, metaStore);
    addStore(kServiceProviderAccountStore, accountStore);
}

ServiceProviderStorage::~ServiceProviderStorage()
{
    if (isOpened())
        close();
}

void ServiceProviderStorage::close()
{
    Store* store = metaStore();
    Q_ASSERT(store);
    if (store)
        store->close();

    store = accountStore();
    Q_ASSERT(store);
    if (store)
        store->close();
}

void ServiceProviderStorage::open()
{
    Store* store = metaStore();
    Q_ASSERT(store);
    if (store)
        store->open();

    store = accountStore();
    Q_ASSERT(store);
    if (store)
        store->open();
}

void ServiceProviderStorage::remove()
{
    QScopedPointer<StorageTransaction> trans(beginTransaction());

    Store *meta = metaStore();
    Store *account = accountStore();
    Q_ASSERT(meta && account);

    try {
        meta->remove();
        account->remove();
        trans->commit();
    } catch (Exceptions::StorageException& e) {
        qLog() << e.what();
        throw;
    }
}

void ServiceProviderStorage::upgrade(int fromVersion)
{
    QScopedPointer<StorageTransaction> trans(beginTransaction());

    Store *meta = metaStore();
    Store *account = accountStore();
    Q_ASSERT(meta && account);

    try {
        meta->upgrade(fromVersion);
        account->upgrade(fromVersion);
        trans->commit();
    } catch (Exceptions::StorageException& e) {
        qLog() << e.what();
        throw;
    }
}

int ServiceProviderStorage::version() const
{
    Q_D(const ServiceProviderStorage);
}

ServiceProviderInfo *ServiceProviderStorage::getProviderInfo() const
{
    Q_D(const ServiceProviderStorage);
}

bool ServiceProviderStorage::isOpened() const
{
    Q_D(const ServiceProviderStorage);
}

StorageTransaction *ServiceProviderStorage::beginTransaction(
    StorageTransaction *parentTransaction)
{
    return 0;
}

ServiceProviderMetaStore *ServiceProviderStorage::metaStore()
{
    return static_cast<ServiceProviderMetaStore*>(
        store(kServiceProviderMetaStore));
}

ServiceProviderAccountStore *ServiceProviderStorage::accountStore()
{
    return static_cast<ServiceProviderAccountStore*>(
        store(kServiceProviderAccountStore));
}

} // namespace Storage
} // namespace Services
} // namespace Maily
