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

#ifndef SERVICEPROVIDERSTORAGETRANSACTION_H
#define SERVICEPROVIDERSTORAGETRANSACTION_H

#include "storagetransaction.h"

#include <QObject>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class ServiceProviderStorageTransactionPrivate;
class ServiceProviderStorageTransaction : public StorageTransaction
{
    Q_OBJECT

public:
    explicit ServiceProviderStorageTransaction(
        ServiceProviderStorageTransaction *parent = 0);
    virtual ~ServiceProviderStorageTransaction();
    
    virtual void commit();
    virtual void rollback();

signals:
    
public slots:

private:
    Q_DISABLE_COPY(ServiceProviderStorageTransaction)
    Q_DECLARE_PRIVATE(ServiceProviderStorageTransaction)
    QScopedPointer<ServiceProviderStorageTransactionPrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // SERVICEPROVIDERSTORAGETRANSACTION_H
