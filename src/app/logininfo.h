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

class LoginInfo : public QObject
{
    Q_OBJECT
public:
    explicit LoginInfo(QObject *parent = 0);

signals:

public slots:

};

} // namespace Services
} // namespace Maily

#endif // LOGININFO_H
