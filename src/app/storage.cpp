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

#include "storage.h"
#include "store.h"

#include <QMap>
#include <QSharedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

Storage::Storage(QObject *parent) :
    QObject(parent)
{
}

Storage::~Storage()
{
}

Store *Storage::store(const QString &storeName)
{
    return findChild<Store*>(storeName);
}

void Storage::addStore(const QString &storeName, Store *store)
{
    store->setParent(this);
    store->setObjectName(storeName);
}

void Storage::removeStore(const QString &storeName)
{
    Store *store = findChild<Store*>(storeName);
    Q_ASSERT(store);
    delete store;
}

} // namespace Storage
} // namespace Services
} // namespace Maily
