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
#include "serviceproviderstoragetransaction.h"
#include "serviceproviderstoragetransactionprivate.h"
#include "storageexception.h"
#include "tools.h"

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/sqlite/database.hxx>

#include <QScopedPointer>
#include <QSharedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class ServiceProviderStoragePrivate
{
public:
    ServiceProviderStoragePrivate(const QString& fileName) :
        database_(new odb::sqlite::database(fileName.toStdString(),
            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE))
    {
    }

    QSharedPointer<odb::database> database_;
};

ServiceProviderStorage::ServiceProviderStorage(QObject *parent,
    const QString &storageName, int version, ServiceProviderMetaStore *metaStore,
    ServiceProviderAccountStore *accountStore) :
    Storage(parent, storageName, version),
    d_ptr(new ServiceProviderStoragePrivate(storageName))
{
    Q_ASSERT(metaStore);
    if (metaStore)
        addStore(metaStore->name(), metaStore);

    Q_ASSERT(accountStore);
    if (accountStore)
        addStore(accountStore->name(), accountStore);
}

ServiceProviderStorage::~ServiceProviderStorage()
{
    if (isOpened())
        close();
}

void ServiceProviderStorage::close()
{
    Store *meta = metaStore();
    Store *account = accountStore();
    Q_ASSERT(meta && account);
    if (!meta || !account)
        return;

    QScopedPointer<StorageTransaction> trans(beginTransaction());

    try {
        meta->close();
        account->close();
        trans->commit();
    } catch (Exceptions::StorageException &e) {
        qLog() << e.what();
    }
}

void ServiceProviderStorage::open()
{
    Store *meta = metaStore();
    Store *account = accountStore();
    Q_ASSERT(meta && account);
    if (!meta || !account)
        return;

    QScopedPointer<StorageTransaction> trans(beginTransaction());

    try {
        meta->open();
        account->open();
        trans->commit();
    } catch (Exceptions::StorageException &e) {
        qLog() << e.what();
    }
}

void ServiceProviderStorage::remove()
{
    Store *meta = metaStore();
    Store *account = accountStore();
    Q_ASSERT(meta && account);
    if (!meta || !account)
        return;

    QScopedPointer<StorageTransaction> trans(beginTransaction());

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

    Store *meta = metaStore();
    Store *account = accountStore();
    Q_ASSERT(meta && account);
    if (!meta || !account)
        return;

    QScopedPointer<StorageTransaction> trans(beginTransaction());

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
    const ServiceProviderMetaStore *meta =
        static_cast<const ServiceProviderMetaStore*>(metaStore());
    Q_ASSERT(meta);
    return meta->getServiceStorageVersion();
}

ServiceProviderInfo *ServiceProviderStorage::getProviderInfo() const
{
    return 0;
}

bool ServiceProviderStorage::isOpened() const
{
    const Store *meta = metaStore();
    const Store *account = accountStore();
    Q_ASSERT(meta && account);
    if (!meta || !account)
        return false;

    return meta->isOpened() && account->isOpened();
}

StorageTransaction *ServiceProviderStorage::beginTransaction(
    StorageTransaction *parentTransaction)
{
    Q_UNUSED(parentTransaction);
    Q_D(ServiceProviderStorage);

    QScopedPointer<ServiceProviderStorageTransaction> trans(
        new ServiceProviderStorageTransaction);
    QScopedPointer<odb::transaction> t(new odb::transaction(d->database_->begin()));
    trans->d_ptr->t_.reset(t.take());
    return trans.take();
}

ServiceProviderMetaStore *ServiceProviderStorage::metaStore()
{
    return static_cast<ServiceProviderMetaStore*>(
                store(kServiceProviderMetaStore));
}

const ServiceProviderMetaStore *ServiceProviderStorage::metaStore() const
{
    return metaStore();
}

ServiceProviderAccountStore *ServiceProviderStorage::accountStore()
{
    return static_cast<ServiceProviderAccountStore*>(
                store(kServiceProviderAccountStore));
}

const ServiceProviderAccountStore *ServiceProviderStorage::accountStore() const
{
    return accountStore();
}

odb::database *ServiceProviderStorage::database()
{
    Q_D(ServiceProviderStorage);
    return d->database_.data();
}

const odb::database *ServiceProviderStorage::database() const
{
    return database();
}

} // namespace Storage
} // namespace Services
} // namespace Maily
