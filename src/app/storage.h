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

#ifndef STORAGE_H
#define STORAGE_H

#include "storagetransaction.h"

#include <QObject>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class StoragePrivate;
class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);
    virtual ~Storage();
    
    virtual bool close() = 0;
    virtual bool open() = 0;
    virtual bool remove() = 0;
    virtual bool upgrade(int fromVersion) = 0;
    virtual int version() const = 0;
    virtual bool isOpened() const = 0;

    virtual StorageTransaction* beginTransaction(
        StorageTransaction *parentTransaction = 0) = 0;

signals:
    
public slots:
    
private:
    Q_DISABLE_COPY(Storage)
    Q_DECLARE_PRIVATE(Storage)
    QScopedPointer<StoragePrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // STORAGE_H
