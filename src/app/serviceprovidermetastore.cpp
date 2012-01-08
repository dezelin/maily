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

#include "serviceprovidermetastore.h"
#include "serviceproviderstorage.h"

#include "serviceprovidermetastore-odb.hxx"
#include <odb/database.hxx>

namespace Maily
{
namespace Services
{
namespace Storage
{

using namespace odb::core;

class ServiceProviderMetaStorePrivate
{
public:
    ServiceProviderMetaStorePrivate()
    {

    }
};

ServiceProviderMetaStore::ServiceProviderMetaStore(QObject *parent,
    const QString &storeName, int version) :
    Store(parent, storeName, version), d_ptr(new ServiceProviderMetaStorePrivate())
{
}

ServiceProviderMetaStore::~ServiceProviderMetaStore()
{
}

unsigned int ServiceProviderMetaStore::getServiceStorageVersion() const
{
    ServiceProviderStorage *storage = dynamic_cast<ServiceProviderStorage*>(parent());
    Q_ASSERT(storage);
    if (!storage)
        return 0;

    odb::database *db = storage->database();
    Q_ASSERT(db);
    if (!db)
        return 0;

    typedef odb::query<Odb::ServiceProviderMetaStore> query;
    typedef odb::result<Odb::ServiceProviderMetaStore> result;

    result r(db->query<Odb::ServiceProviderMetaStore>(query::id > 30));

    return 0;
}

} // namespace Storage
} // namespace Services
} // namespace Maily
