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

#ifndef STORAGEEXCEPTION_H
#define STORAGEEXCEPTION_H

#include <exception>
#include <QObject>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Storage
{
namespace Exceptions
{

class StorageExceptionPrivate;
class StorageException : public std::exception
{
public:
    StorageException();
    StorageException(const std::exception &e);
    virtual ~StorageException() throw();

    StorageException(const StorageException &e);
    StorageException &operator =(const StorageException &e);
    const StorageException &operator =(const StorageException &e) const;

    void swap(StorageException &e);

    virtual const char *what() const throw();

private:
    Q_DECLARE_PRIVATE(StorageException)
    QScopedPointer<StorageExceptionPrivate> d_ptr;
};

} // namespace Exceptions
} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // STORAGEEXCEPTION_H
