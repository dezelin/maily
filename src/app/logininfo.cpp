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

class LoginInfoPrivate
{
public:
    LoginInfoPrivate()
    {
    }

    LoginInfoPrivate(const QString& username, const QString& password) :
        m_username(username), m_password(password)
    {
    }

    LoginInfoPrivate(const LoginInfoPrivate& d)
    {
        *this = d;
    }

    LoginInfoPrivate& operator= (const LoginInfoPrivate& d)
    {
        if (this == &d)
            return *this;

        LoginInfoPrivate tmp(d);
        swap(tmp);
        return *this;
    }

    const LoginInfoPrivate& operator= (const LoginInfoPrivate& d) const
    {
        return (*this = d);
    }

    void swap(LoginInfoPrivate& d)
    {
        m_username.swap(d.m_username);
        m_password.swap(d.m_password);
    }

    QString m_username;
    QString m_password;
};

LoginInfo::LoginInfo() :
    d_ptr(new LoginInfoPrivate())
{
}

LoginInfo::LoginInfo(const QString& username, const QString& password) :
    d_ptr(new LoginInfoPrivate(username, password))
{
}

LoginInfo::~LoginInfo()
{
}

LoginInfo::LoginInfo(const LoginInfo& loginInfo)
{
    *this = loginInfo;
}

LoginInfo& LoginInfo::operator= (const LoginInfo& loginInfo)
{
    if (this == & loginInfo)
        return *this;

    LoginInfo tmp(loginInfo);
    swap(tmp);
    return *this;
}

const LoginInfo& LoginInfo::operator= (const LoginInfo& loginInfo) const
{
    return (*this = loginInfo);
}

void LoginInfo::swap(LoginInfo& loginInfo)
{
    d_ptr.swap(loginInfo.d_ptr);
}

const QString& LoginInfo::password() const
{
    Q_D(const LoginInfo);
    return d->m_password;
}

void LoginInfo::setPassword(const QString &password)
{
    Q_D(LoginInfo);
    d->m_password = password;
}

const QString& LoginInfo::username() const
{
    Q_D(const LoginInfo);
    return d->m_username;
}

void LoginInfo::setUsername(const QString &username)
{
    Q_D(LoginInfo);
    d->m_username = username;
}

} // namespace Services
} // namespace Maily
