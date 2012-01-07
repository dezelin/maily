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

#include "storageexception.h"

namespace Maily
{
namespace Services
{
namespace Storage
{
namespace Exceptions
{

class StorageExceptionPrivate
{
public:
    StorageExceptionPrivate()
    {
    }

    StorageExceptionPrivate(const std::exception &e) :
        e_(e)
    {
    }

    StorageExceptionPrivate(const StorageExceptionPrivate &e) :
        e_(e.e_)
    {
    }

    StorageExceptionPrivate &operator =(const StorageExceptionPrivate &e)
    {
        if (this == &e)
            return *this;

        StorageExceptionPrivate tmp(e);
        swap(tmp);
        return *this;
    }

    const StorageExceptionPrivate &operator =(const StorageExceptionPrivate &e) const
    {
        return (*this = e);
    }

    void swap(StorageExceptionPrivate &e)
    {
        std::swap(e_, e.e_);
    }

    std::exception e_;
};

StorageException::StorageException() :
    std::exception(), d_ptr(new StorageExceptionPrivate())
{
}

StorageException::StorageException(const std::exception &e) :
    std::exception(), d_ptr(new StorageExceptionPrivate(e))
{
}

StorageException::~StorageException() throw()
{
}

StorageException::StorageException(const StorageException &e) :
    std::exception(e)
{
    Q_ASSERT(e.d_ptr);
    QScopedPointer<StorageExceptionPrivate> tmp(new StorageExceptionPrivate(*e.d_ptr));
    d_ptr.swap(tmp);
}

StorageException &StorageException::operator =(const StorageException &e)
{
    if (this == &e)
        return *this;

    StorageException tmp(e);
    swap(tmp);
    return *this;
}

const StorageException &StorageException::operator =(const StorageException &e) const
{
    return (*this = e);
}

void StorageException::swap(StorageException &e)
{
    d_ptr.swap(e.d_ptr);
}

const char *StorageException::what() const throw()
{
    Q_D(const StorageException);
    return d->e_.what();
}

} // namespace Exceptions
} // namespace Storage
} // namespace Services
} // namespace Maily
