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

#ifndef SERVICEPROVIDERSTORAGE_H
#define SERVICEPROVIDERSTORAGE_H

#include "serviceproviderinfo.h"
#include "serviceprovidermetastore.h"
#include "serviceprovideraccountstore.h"
#include "storage.h"
#include "storagetransaction.h"
#include "store.h"

#include <QObject>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class ServiceProviderStoragePrivate;
class ServiceProviderStorage : public Storage
{
    Q_OBJECT

public:
    explicit ServiceProviderStorage(QObject *parent,
        ServiceProviderMetaStore *metaStore,
        ServiceProviderAccountStore *accountStore);
    virtual ~ServiceProviderStorage();

    virtual void close();
    virtual void open();
    virtual void remove();
    virtual void upgrade(int fromVersion);
    virtual int version() const;
    virtual bool isOpened() const;

    virtual ServiceProviderInfo *getProviderInfo() const;

    virtual StorageTransaction *beginTransaction(
        StorageTransaction *parentTransaction = 0);

signals:
    
public slots:

protected:
    ServiceProviderMetaStore *metaStore();
    const ServiceProviderMetaStore *metaStore() const;

    ServiceProviderAccountStore *accountStore();
    const ServiceProviderAccountStore *accountStore() const;

private:
    Q_DISABLE_COPY(ServiceProviderStorage)
    Q_DECLARE_PRIVATE(ServiceProviderStorage)
    QScopedPointer<ServiceProviderStoragePrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // SERVICEPROVIDERSTORAGE_H
