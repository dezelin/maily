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
#include "store.h"

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
    explicit Storage(QObject *parent, const QString& storageName, int version = 1);
    virtual ~Storage();
    
    virtual void close() = 0;
    virtual void open() = 0;
    virtual void remove() = 0;
    virtual void upgrade(int fromVersion) = 0;
    virtual int version() const = 0;
    virtual bool isOpened() const = 0;
    virtual const QString name() const;

    virtual StorageTransaction* beginTransaction(
        StorageTransaction *parentTransaction = 0) = 0;

signals:
    
public slots:

protected:
    Store *store(const QString &storeName);
    void addStore(const QString &storeName, Store *store);
    void removeStore(const QString &storeName);

private:
    Q_DISABLE_COPY(Storage)
    Q_DECLARE_PRIVATE(Storage)
    QScopedPointer<StoragePrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // STORAGE_H
