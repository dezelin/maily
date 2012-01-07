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

#ifndef EMAILSERVICEPROVIDERSTORAGE_H
#define EMAILSERVICEPROVIDERSTORAGE_H

#include "serviceprovidermetastore.h"
#include "serviceprovideraccountstore.h"
#include "serviceproviderstorage.h"
#include "store.h"

#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class EmailServiceProviderStoragePrivate;
class EmailServiceProviderStorage : public ServiceProviderStorage
{
    Q_OBJECT
public:
    explicit EmailServiceProviderStorage(QObject *parent, const QString& storageName,
        ServiceProviderMetaStore *meta, ServiceProviderAccountStore *account,
        Store *data, int version = 1);

    virtual ~EmailServiceProviderStorage();


signals:
    
public slots:

private:
    Q_DISABLE_COPY(EmailServiceProviderStorage)
    Q_DECLARE_PRIVATE(EmailServiceProviderStorage)
    QScopedPointer<EmailServiceProviderStoragePrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // EMAILSERVICEPROVIDERSTORAGE_H
