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

#include "tools.h"
#include "serviceprovidermetastore.h"
#include "serviceproviderstorage.h"
#include "storageexception.h"
#include "serviceprovidermetastore-odb.hxx"

#include <odb/database.hxx>
#include <odb/schema-catalog.hxx>
#include <exception>

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
    const QString &storeName, unsigned int version) :
    Store(parent, storeName, version),
    d_ptr(new ServiceProviderMetaStorePrivate())
{
}

ServiceProviderMetaStore::~ServiceProviderMetaStore()
{
}

bool ServiceProviderMetaStore::create()
{
}

bool ServiceProviderMetaStore::open()
{
    ServiceProviderStorage *storage = dynamic_cast<ServiceProviderStorage*>(parent());
    Q_ASSERT(storage);
    if (!storage)
        return false;

    odb::database *db = storage->database();
    Q_ASSERT(db);
    if (!db)
        return false;

    try {
        odb::transaction t(db->begin());

        typedef odb::query<Odb::ServiceProviderMetaStore> query;
        typedef odb::result<Odb::ServiceProviderMetaStore> result;

        result r(db->query<Odb::ServiceProviderMetaStore>());
        result::iterator it(r.begin());
        if (it == r.end())
            return false;

        setVersion(it->version());
        t.commit();

    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return true;
}

bool ServiceProviderMetaStore::remove()
{
    ServiceProviderStorage *storage = dynamic_cast<ServiceProviderStorage*>(parent());
    Q_ASSERT(storage);
    if (!storage)
        return false;

    odb::database *db = storage->database();
    Q_ASSERT(db);
    if (!db)
        return false;

    try {
        odb::transaction t(db->begin());
        db->erase_query<Odb::ServiceProviderMetaStore>();
        t.commit();
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return true;
}

unsigned int ServiceProviderMetaStore::getServiceStorageVersion() const
{
    Q_ASSERT(isOpened());
    if (!isOpened())
        return -1;

    return version();
}

} // namespace Storage
} // namespace Services
} // namespace Maily
