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

#ifndef SMARTLIST_H
#define SMARTLIST_H

#include "tools.h"

#include <QList>

namespace Maily
{
namespace Containers
{

template <typename T>
class SmartList : public QList<T>
{
    typedef char PointerType;
    typedef char ScalarType[2];

    template<typename H>
    struct is_pointer { typedef ScalarType type; };

    template<typename H>
    struct is_pointer<H*> { typedef PointerType type; };

    void deleteAll(ScalarType&) {}
    void deleteAll(PointerType&) { qDeleteAll(*this); }

public:
    ~SmartList()
    {
        typename is_pointer<T>::type r;
        deleteAll(r);
    }

private:
};

} // namespace Containers
} // namespace Maily

#endif // SMARTLIST_H
