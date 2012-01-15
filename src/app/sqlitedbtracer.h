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

#ifndef SQLITEDBTRACER_H
#define SQLITEDBTRACER_H

#include <odb/core.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/statement.hxx>
#include <odb/sqlite/tracer.hxx>

namespace Maily
{
namespace Services
{
namespace Storage
{

class SqliteDbTracer : public odb::sqlite::tracer
{
public:
    SqliteDbTracer();
    virtual ~SqliteDbTracer();

    virtual void prepare (odb::sqlite::connection &connection,
        const odb::sqlite::statement &statement);
    virtual void execute (odb::sqlite::connection &connection,
        const odb::sqlite::statement &statement);
    virtual void execute (odb::sqlite::connection &connection,
        const char *statement);
    virtual void deallocate (odb::sqlite::connection &connection,
        const odb::sqlite::statement &statement);
};

} // namespace Storage
} // namespace Services
} // namespace Maily

#endif // SQLITEDBTRACER_H
