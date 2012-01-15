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

#include "emailserviceprovideraccountstore.h"
#include "emailserviceprovideraccountstore-odb.hxx"
#include "emailserviceproviderinfo.h"
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

EmailServiceProviderAccountStore::EmailServiceProviderAccountStore(QObject *parent,
    const QString &storeName, int version) :
    ServiceProviderAccountStore(parent, storeName, version)
{
    setProviderInfo(new EmailServiceProviderInfo());
}

EmailServiceProviderAccountStore::~EmailServiceProviderAccountStore()
{
}

bool EmailServiceProviderAccountStore::close()
{
    bool updated = update();
    Q_ASSERT(updated);
    if (!updated)
        return false;

    return ServiceProviderAccountStore::close();
}

bool EmailServiceProviderAccountStore::create()
{
    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool created = false;

    try {
        odb::transaction t(db->begin());
        odb::schema_catalog::create_schema(*db,
            kEmailServiceProviderAccountStore.toLower().toStdString());
        t.commit();
        created = true;
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return created;
}

bool EmailServiceProviderAccountStore::open()
{
    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool opened = false;

    try {
        odb::transaction t(db->begin());
        typedef odb::query<Odb::EmailServiceProviderAccountStore> query;
        typedef odb::result<Odb::EmailServiceProviderAccountStore> result;

        result r(db->query<Odb::EmailServiceProviderAccountStore>());
        result::iterator it(r.begin());
        if (it == r.end())
            return false;

        QScopedPointer<EmailServiceProviderInfo> providerInfo(
            new EmailServiceProviderInfo());
        providerInfo->setAddress(it->address());
        providerInfo->setAuthenticationType(
            static_cast<EmailServiceProviderInfo::AuthenticationTypes>(
                it->authenticationType()));
        providerInfo->setDisplayName(it->displayName());
        providerInfo->setDisplayShortName(it->displayShortName());
        providerInfo->setPassword(it->password());
        providerInfo->setPort(it->port());
        providerInfo->setRootPath(it->rootPath());
        providerInfo->setSendmailBinPath(it->sendmailBinPath());
        providerInfo->setServiceType(
            static_cast<EmailServiceProviderInfo::ServiceTypes>(it->serviceType()));
        providerInfo->setTls(it->tls());
        providerInfo->setTlsRequired(it->tlsRequired());
        providerInfo->setUsername(it->username());
        setProviderInfo(providerInfo.take());
        t.commit();
        opened = true;
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return opened;
}

bool EmailServiceProviderAccountStore::remove()
{
    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    bool removed = false;

    try {
        odb::transaction t(db->begin());
        db->erase_query<Odb::EmailServiceProviderAccountStore>();
        db->execute(QString("DROP TABLE IF EXISTS \"%1\"").
            arg(kEmailServiceProviderAccountStore).toStdString());
        t.commit();
        removed = true;
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return removed;
}

bool EmailServiceProviderAccountStore::update()
{
    odb::database *db = database();
    Q_ASSERT(db);
    if (!db)
        return false;

    EmailServiceProviderInfo* providerInfo =
        static_cast<EmailServiceProviderInfo*>(getProviderInfo());
    Q_ASSERT(providerInfo);
    if (!providerInfo)
        return false;

    bool updated = false;

    try {
        odb::transaction t(db->begin());
        typedef odb::query<Odb::EmailServiceProviderAccountStore> query;
        typedef odb::result<Odb::EmailServiceProviderAccountStore> result;

        Odb::EmailServiceProviderAccountStore accountStore;
        result r(db->query<Odb::EmailServiceProviderAccountStore>());
        result::iterator it(r.begin());
        if (it != r.end())
            accountStore = *it;

        accountStore.setAddress(providerInfo->address());
        accountStore.setAuthenticationType(providerInfo->authenticationType());
        accountStore.setDisplayName(providerInfo->displayName());
        accountStore.setDisplayShortName(providerInfo->displayShortName());
        accountStore.setPassword(providerInfo->password());
        accountStore.setPort(providerInfo->port());
        accountStore.setRootPath(providerInfo->rootPath());
        accountStore.setSendmailBinPath(providerInfo->sendmailBinPath());
        accountStore.setServiceType(providerInfo->serviceType());
        accountStore.setTls(providerInfo->tls());
        accountStore.setTlsRequired(providerInfo->tlsRequired());
        accountStore.setUsername(providerInfo->username());
        db->update(accountStore);
        t.commit();
        updated = true;
    } catch (std::exception &e) {
        qLog() << e.what();
    }

    return updated;
}

} // namespace Storage
} // namespace Services
} // namespace Maily
