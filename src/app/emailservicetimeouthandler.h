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

#ifndef EMAILSERVICETIMEOUTHANDLER_H
#define EMAILSERVICETIMEOUTHANDLER_H

#include <QScopedPointer>
#include <vmime/vmime.hpp>

namespace Maily
{
namespace Services
{

class EmailServiceTimeoutHandlerPrivate;
class EmailServiceTimeoutHandler : public vmime::net::timeoutHandler
{
public:
    EmailServiceTimeoutHandler(unsigned int timeout = 30);
    virtual ~EmailServiceTimeoutHandler();

    virtual bool isTimeOut();
    virtual void resetTimeOut();
    virtual bool handleTimeOut();

private:
    unsigned int getTime() const;

private:
    Q_DISABLE_COPY(EmailServiceTimeoutHandler)
    Q_DECLARE_PRIVATE(EmailServiceTimeoutHandler)
    QScopedPointer<EmailServiceTimeoutHandlerPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // EMAILSERVICETIMEOUTHANDLER_H
