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

#include "emailservicetimeouthandler.h"

namespace Maily
{
namespace Services
{

class EmailServiceTimeoutHandlerPrivate
{
public:
    EmailServiceTimeoutHandlerPrivate(unsigned int t) :
        timeout(t), lastTime(0)
    {
    }

    unsigned int timeout;
    unsigned int lastTime;
};

EmailServiceTimeoutHandler::EmailServiceTimeoutHandler(unsigned int timeout)
    : vmime::net::timeoutHandler(), d_ptr(new EmailServiceTimeoutHandlerPrivate(timeout))
{
}

EmailServiceTimeoutHandler::~EmailServiceTimeoutHandler()
{
}

bool EmailServiceTimeoutHandler::isTimeOut()
{
    Q_D(const EmailServiceTimeoutHandler);

    return getTime() >= d->lastTime + d->timeout;
}

void EmailServiceTimeoutHandler::resetTimeOut()
{
    Q_D(EmailServiceTimeoutHandler);

    d->lastTime = getTime();
}

bool EmailServiceTimeoutHandler::handleTimeOut()
{
    return false;
}

unsigned int EmailServiceTimeoutHandler::getTime() const
{
    return vmime::platform::getHandler()->getUnixTime();
}

} // namespace Services
} // namespace Maily

