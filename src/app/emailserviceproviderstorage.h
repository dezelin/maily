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

#include "serviceproviderstorage.h"

namespace Maily
{
namespace Services
{
namespace Storage
{

class EmailServiceProviderStorage : public ServiceProviderStorage
{
    Q_OBJECT
public:
    explicit EmailServiceProviderStorage(QObject *parent = 0);
    
signals:
    
public slots:
    
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // EMAILSERVICEPROVIDERSTORAGE_H
