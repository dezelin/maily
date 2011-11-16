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

#ifndef BUSYINDICATORWIDGET_H
#define BUSYINDICATORWIDGET_H

#include <QWidget>

namespace Maily
{
namespace Widgets
{

namespace details
{
  struct BusyIndicatorWidgetPrivate;
}

class BusyIndicatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BusyIndicatorWidget(QWidget *parent = 0);
    virtual ~BusyIndicatorWidget();

signals:

public slots:
  void resume();
  void start();
  void stop();

private slots:
  void rotateSpinner(int value);

private:
  details::BusyIndicatorWidgetPrivate* m_data;
};

} // namespace widgets
} // namespace maily

#endif // BUSYINDICATORWIDGET_H
