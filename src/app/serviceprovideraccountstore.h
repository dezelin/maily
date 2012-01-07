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

#ifndef SERVICEPROVIDERACCOUNTSTORE_H
#define SERVICEPROVIDERACCOUNTSTORE_H

#include "serviceproviderinfo.h"
#include "store.h"

#include <QObject>

namespace Maily
{
namespace Services
{
namespace Storage
{

const QString kServiceProviderAccountStore = "ServiceProviderAccountStore";

class ServiceProviderAccountStore : public Store
{
    Q_OBJECT

public:
    explicit ServiceProviderAccountStore(QObject *parent,
        const QString &storeName = kServiceProviderAccountStore, int version = 1);
    virtual ~ServiceProviderAccountStore();
    
    ServiceProviderInfo* getProviderInfo() const;

signals:
    
public slots:
    
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // SERVICEPROVIDERACCOUNTSTORE_H
