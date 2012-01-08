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

#include "serviceproviderstoragetransaction.h"
#include "serviceproviderstoragetransactionprivate.h"

namespace Maily
{
namespace Services
{
namespace Storage
{

ServiceProviderStorageTransaction::ServiceProviderStorageTransaction(
    ServiceProviderStorageTransaction *parent) :
    StorageTransaction(parent), d_ptr(new ServiceProviderStorageTransactionPrivate())
{
}

ServiceProviderStorageTransaction::~ServiceProviderStorageTransaction()
{
}

void ServiceProviderStorageTransaction::commit()
{
    Q_D(ServiceProviderStorageTransaction);
    Q_ASSERT(d->t_);
    if (!d->t_)
        return;

    d->t_->commit();
}

void ServiceProviderStorageTransaction::rollback()
{
    Q_D(ServiceProviderStorageTransaction);
    Q_ASSERT(d->t_);
    if (!d->t_)
        return;

    d->t_->rollback();
}

} // namespace Storage
} // namespace Services
} // namespace Maily
