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

#ifndef EMAILSERVICETIMEOUTHANDLERFACTORY_H
#define EMAILSERVICETIMEOUTHANDLERFACTORY_H

#include "emailservicetimeouthandler.h"

#include <vmime/vmime.hpp>

namespace Maily
{
namespace Services
{

class EmailServiceTimeoutHandlerFactory : public vmime::net::timeoutHandlerFactory
{
public:
    EmailServiceTimeoutHandlerFactory();

    vmime::ref<vmime::net::timeoutHandler> create();
};

} // namespace Services
} // namespace Maily

#endif // EMAILSERVICETIMEOUTHANDLERFACTORY_H
