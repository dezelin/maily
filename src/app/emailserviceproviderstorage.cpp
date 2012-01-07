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

#include "emailserviceproviderstorage.h"
#include "store.h"

#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class EmailServiceProviderStoragePrivate
{
public:
    EmailServiceProviderStoragePrivate()
    {
    }

};

EmailServiceProviderStorage::EmailServiceProviderStorage(QObject *parent,
    const QString &storageName, ServiceProviderMetaStore *meta,
    ServiceProviderAccountStore *account, Store *data, int version) :
    ServiceProviderStorage(parent, storageName, version, meta, account),
    d_ptr(new EmailServiceProviderStoragePrivate())
{
}

EmailServiceProviderStorage::~EmailServiceProviderStorage()
{
}

} // namespace Storage
} // namespace Services
} // namespace Maily

