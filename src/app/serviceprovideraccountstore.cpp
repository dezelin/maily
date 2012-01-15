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
    Q_ASSERT(isOpened());
    if (!isOpened())
        return false;

    bool updated = update();
    Q_ASSERT(updated);
    if (!updated)
        return false;

    return Store::close();
}

bool ServiceProviderAccountStore::create()
{
    if (!Store::create())
        return false;

    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool created = false;

    try {
        odb::transaction t(db->begin());
        odb::schema_catalog::create_schema(*db,
            kServiceProviderAccountStore.toLower().toStdString());
        t.commit();
        created = true;

    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return created;
}

bool ServiceProviderAccountStore::open()
{
    Q_D(ServiceProviderAccountStore);

    if (!Store::open())
        return false;

    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool opened = false;

    try {
        odb::transaction t(db->begin());

        typedef odb::query<Odb::ServiceProviderAccountStore> query;
        typedef odb::result<Odb::ServiceProviderAccountStore> result;

        result r(db->query<Odb::ServiceProviderAccountStore>());
        result::iterator it(r.begin());
        if (it == r.end())
            return false;

        d->providerInfo_->setUsername(it->username());
        d->providerInfo_->setPassword(it->password());
        d->providerInfo_->setAddress(it->address());
        d->providerInfo_->setPort(it->port());
        d->providerInfo_->setDisplayName(it->displayName());
        d->providerInfo_->setDisplayShortName(it->displayShortName());
        t.commit();
        opened = true;
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return opened;
}

bool ServiceProviderAccountStore::remove()
{
    if (!Store::remove())
        return false;

    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool removed = false;

    try {
        odb::transaction t(db->begin());
        db->erase_query<Odb::ServiceProviderAccountStore>();
        db->execute(QString("DROP TABLE IF EXISTS \"%1\"").
            arg(kServiceProviderAccountStore).toStdString());
        t.commit();
        removed = true;
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return removed;
}

bool ServiceProviderAccountStore::update()
{
    Q_D(const ServiceProviderAccountStore);

    if (!Store::update())
        return false;

    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool updated = false;

    try {
        odb::transaction t(db->begin());

        typedef odb::query<Odb::ServiceProviderAccountStore> query;
        typedef odb::result<Odb::ServiceProviderAccountStore> result;

        Odb::ServiceProviderAccountStore as;
        result r(db->query<Odb::ServiceProviderAccountStore>());
        result::iterator it(r.begin());
        if (it != r.end())
            as = *it;

        as.setUsername(d->providerInfo_->username());
        as.setPassword(d->providerInfo_->password());
        as.setAddress(d->providerInfo_->address());
        as.setPort(d->providerInfo_->port());
        as.setDisplayName(d->providerInfo_->displayName());
        as.setDisplayShortName(d->providerInfo_->displayShortName());
        db->update(as);
        t.commit();
        updated = true;

    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return updated;
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
