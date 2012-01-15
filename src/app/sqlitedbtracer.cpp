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

#include "sqlitedbtracer.h"
#include "tools.h"

#include <odb/sqlite/database.hxx>

namespace Maily
{
namespace Services
{
namespace Storage
{

SqliteDbTracer::SqliteDbTracer()
{
}

SqliteDbTracer::~SqliteDbTracer()
{
}

void SqliteDbTracer::prepare(odb::sqlite::connection &connection,
    const odb::sqlite::statement &statement)
{
    qLog() << connection.database().name().c_str() << ": PREPARE "
           << statement.text() << endl;
}

void SqliteDbTracer::execute(odb::sqlite::connection &connection,
    const odb::sqlite::statement &statement)
{
    qLog() << connection.database().name().c_str() << ": EXECUTE "
           << statement.text() << endl;
}

void SqliteDbTracer::execute(odb::sqlite::connection &connection,
    const char *statement)
{
    qLog() << connection.database().name().c_str() << ": EXECUTE "
           << statement << endl;
}

void SqliteDbTracer::deallocate(odb::sqlite::connection &connection,
    const odb::sqlite::statement &statement)
{
    qLog() << connection.database().name().c_str() << ": DEALLOCATE "
           << statement.text() << endl;
}

} // namespace Storage
} // namespace Services
} // namespace Maily
