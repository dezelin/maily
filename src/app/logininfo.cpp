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

#include "logininfo.h"

namespace Maily
{
namespace Services
{

struct LoginInfo::LoginInfoPrivate
{
    QString m_username;
    QString m_password;
};

LoginInfo::LoginInfo(QObject *parent) :
    QObject(parent), m_data(new LoginInfoPrivate())
{
}

LoginInfo::~LoginInfo()
{
}

const QString& LoginInfo::password() const
{
    Q_ASSERT(m_data);
    return m_data->m_password;
}

void LoginInfo::setPassword(const QString &password)
{
    Q_ASSERT(m_data);
    m_data->m_password = password;
}

const QString& LoginInfo::username() const
{
    Q_ASSERT(m_data);
    return m_data->m_username;
}

void LoginInfo::setUsername(const QString &username)
{
    Q_ASSERT(m_data);
    m_data->m_username = username;
}

} // namespace Services
} // namespace Maily
