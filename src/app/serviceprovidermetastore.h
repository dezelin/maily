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

#ifndef SERVICEPROVIDERMETASTORE_H
#define SERVICEPROVIDERMETASTORE_H

#include "serviceproviderinfo.h"
#include "store.h"

#include <QObject>
#include <QScopedPointer>

namespace odb
{
    class database;
}

namespace Maily
{
namespace Services
{
namespace Storage
{

const QString kServiceProviderMetaStore = "ServiceProviderMetaStore";

class ServiceProviderMetaStorePrivate;
class ServiceProviderMetaStore : public Store
{
    Q_OBJECT
public:
    explicit ServiceProviderMetaStore(QObject *parent,
        const QString& storeName = kServiceProviderMetaStore, unsigned int version = 1);
    virtual ~ServiceProviderMetaStore();

    virtual bool create();
    virtual bool open();
    virtual bool remove();

    unsigned int getServiceStorageVersion() const;
    
signals:
    
public slots:

private:
    odb::database* database();
    const odb::database *database() const;

private:
    Q_DISABLE_COPY(ServiceProviderMetaStore)
    Q_DECLARE_PRIVATE(ServiceProviderMetaStore)
    QScopedPointer<ServiceProviderMetaStorePrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // SERVICEPROVIDERMETASTORE_H
