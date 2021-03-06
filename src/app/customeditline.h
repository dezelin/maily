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

#ifndef CUSTOMEDITLINE_H
#define CUSTOMEDITLINE_H

#include <QLineEdit>
#include <QScopedPointer>

namespace Maily
{
namespace Widgets
{

class CustomEditLinePrivate;
class CustomEditLine : public QLineEdit
{
    Q_OBJECT

public:
    CustomEditLine(QWidget *parent = 0);
    virtual ~CustomEditLine();

public:
    void setEmptyMessage( const QString &msg );

protected:
    void paintEvent( QPaintEvent *ev );
    void focusInEvent( QFocusEvent *ev );
    void focusOutEvent( QFocusEvent *ev );

private:
    Q_DISABLE_COPY(CustomEditLine)
    Q_DECLARE_PRIVATE(CustomEditLine)
    QScopedPointer<CustomEditLinePrivate> d_ptr;
};

} // namespace Widgets
} // namespace Maily

#endif // CUSTOMEDITLINE_H
