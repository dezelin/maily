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

#include "store.h"

namespace Maily
{
namespace Services
{
namespace Storage
{

class StorePrivate
{
public:
    StorePrivate(const QString &storeName, int version) :
        opened_(false), version_(version), storeName_(storeName)
    {
    }

    bool opened_;
    int version_;
    QString storeName_;
};

Store::Store(QObject *parent, const QString &storeName, int version) :
    QObject(parent), d_ptr(new StorePrivate(storeName, version))
{
}

Store::~Store()
{
}

void Store::close()
{
    Q_D(Store);
    d->opened_ = false;
}

void Store::create()
{
}

void Store::open()
{
    Q_D(Store);
    d->opened_ = true;
}

void Store::remove()
{
}

void Store::upgrade(int fromVersion)
{
    Q_UNUSED(fromVersion);
}

int Store::version() const
{
    Q_D(const Store);
    return d->version_;
}

bool Store::isOpened() const
{
    Q_D(const Store);
    return d->opened_;
}

} // namespace Storage
} // namespace Services
} // namespace Maily

