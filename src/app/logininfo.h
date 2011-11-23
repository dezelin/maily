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

#ifndef LOGININFO_H
#define LOGININFO_H

#include <QObject>

namespace Maily
{
namespace Services
{

class LoginInfoPrivate;
class LoginInfo
{
public:
    LoginInfo();
    LoginInfo(const QString& username, const QString& password);
    virtual ~LoginInfo();

    LoginInfo(const LoginInfo& loginInfo);
    LoginInfo& operator= (const LoginInfo& loginInfo);
    const LoginInfo& operator= (const LoginInfo& loginInfo) const;

    void swap(LoginInfo& loginInfo);

    const QString& password() const;
    void setPassword(const QString& password);

    const QString& username() const;
    void setUsername(const QString& username);

private:
    Q_DECLARE_PRIVATE(LoginInfo)
    QScopedPointer<LoginInfoPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // LOGININFO_H
