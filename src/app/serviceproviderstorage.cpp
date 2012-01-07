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
    ServiceProviderStoragePrivate(ServiceProviderMetaStore *m,
        ServiceProviderAccountStore *a) :
        meta(m), account(a)
    {
    }

    QScopedPointer<ServiceProviderMetaStore> meta;
    QScopedPointer<ServiceProviderAccountStore> account;
};

ServiceProviderStorage::ServiceProviderStorage(QObject *parent,
    ServiceProviderMetaStore *meta, ServiceProviderAccountStore *account) :
    Storage(parent),
    d_ptr(new ServiceProviderStoragePrivate(meta, account))
{
}

ServiceProviderStorage::~ServiceProviderStorage()
{
    if (!isOpened())
        return;

    close();
}

bool ServiceProviderStorage::close()
{
    Q_D(ServiceProviderStorage);

    bool alreadyOpened = isOpened();
    Q_ASSERT(alreadyOpened);
    if (!alreadyOpened)
        return false;

    bool closed = d->meta->close();
    Q_ASSERT(closed);
    if (closed) {
        closed &= d->account->close();
        Q_ASSERT(closed);
    }

    return closed;
}

bool ServiceProviderStorage::open()
{
    Q_D(ServiceProviderStorage);

    bool alreadyOpened = isOpened();
    Q_ASSERT(!alreadyOpened);
    if (alreadyOpened)
        return false;

    bool opened = d->meta->open();
    Q_ASSERT(opened);
    if (opened) {
        opened &= d->account->open();
        Q_ASSERT(opened);
    }

    return opened;
}

bool ServiceProviderStorage::remove()
{
    Q_D(ServiceProviderStorage);

    if (isOpened())
        if (!close())
            return false;

    QScopedPointer<StorageTransaction> transaction(
        beginTransaction());

    bool removed = false;

    try {
        d->meta->remove();
        d->account->remove();
        transaction->commit();
        removed = true;
    } catch (std::exception& e) {
        qLog() << e.what();
    }

    return removed;
 }

bool ServiceProviderStorage::upgrade(int fromVersion)
{
    Q_D(ServiceProviderStorage);

    if (isOpened())
        if (!close())
            return false;

    QScopedPointer<StorageTransaction> transaction(
        beginTransaction());

    bool upgraded = false;

    try {
        d->meta->upgrade(fromVersion);
        d->account->upgrade(fromVersion);
        transaction->commit();
        upgraded = true;
    } catch (std::exception& e) {
        qLog() << e.what();
    }

    return upgraded;
}

int ServiceProviderStorage::version() const
{
    Q_D(const ServiceProviderStorage);
    return d->meta->version();
}

ServiceProviderInfo *ServiceProviderStorage::getProviderInfo() const
{
    Q_D(const ServiceProviderStorage);
    return d->account->getProviderInfo();
}

bool ServiceProviderStorage::isOpened() const
{
    Q_D(const ServiceProviderStorage);
    return d->meta->isOpened() && d->account->isOpened();
}

StorageTransaction *ServiceProviderStorage::beginTransaction(
    StorageTransaction *parentTransaction)
{
    return 0;
}

} // namespace Storage
} // namespace Services
} // namespace Maily
