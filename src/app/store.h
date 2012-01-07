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

#ifndef STORE_H
#define STORE_H

#include <QObject>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{

class StorePrivate;
class Store : public QObject
{
    Q_OBJECT

public:
    explicit Store(QObject *parent, const QString &storeName, int version = 1);
    virtual ~Store();

    virtual void close();
    virtual void create();
    virtual void open();
    virtual void remove();
    virtual void upgrade(int fromVersion);
    virtual int version() const;
    virtual bool isOpened() const;
    
signals:
    
public slots:

private:
    Q_DISABLE_COPY(Store)
    Q_DECLARE_PRIVATE(Store)
    QScopedPointer<StorePrivate> d_ptr;
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // STORE_H
