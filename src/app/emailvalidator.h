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

#ifndef EMAILVALIDATOR_H
#define EMAILVALIDATOR_H

#include <QRegExpValidator>

namespace Maily
{
namespace Widgets
{
namespace Validators
{

class EmailValidator : public QRegExpValidator
{
    Q_OBJECT

public:
    explicit EmailValidator(QObject* parent = 0);

    virtual void fixup(QString& input) const;
    virtual State validate(QString& str, int& pos) const;
};

} // namespace Validators
} // namespace Widgets
} // namespace Maily

#endif // EMAILVALIDATOR_H
