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

#ifndef BUSYINDICATOR_H
#define BUSYINDICATOR_H

#include <QDeclarativeItem>
#include <QScopedPointer>

namespace Maily
{
namespace Widgets
{

class BusyIndicatorPrivate;
class BusyIndicator : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(qreal innerRadius READ innerRadius WRITE setInnerRadius NOTIFY innerRadiusChanged)
    Q_PROPERTY(qreal outerRadius READ outerRadius WRITE setOuterRadius NOTIFY outerRadiusChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(qreal actualInnerRadius READ actualInnerRadius NOTIFY actualInnerRadiusChanged)
    Q_PROPERTY(qreal actualOuterRadius READ actualOuterRadius NOTIFY actualOuterRadiusChanged)

public:
    explicit BusyIndicator(QDeclarativeItem* parent = 0);
    virtual ~BusyIndicator();

    void setInnerRadius(const qreal& innerRadius);
    qreal innerRadius() const;

    void setOuterRadius(const qreal& outerRadius);
    qreal outerRadius() const;

    void setBackgroundColor(const QColor& color);
    QColor backgroundColor() const;

    void setForegroundColor(const QColor& color);
    QColor foregroundColor() const;

    qreal actualInnerRadius() const;
    qreal actualOuterRadius() const;

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

signals:
    void innerRadiusChanged();
    void outerRadiusChanged();
    void backgroundColorChanged();
    void foregroundColorChanged();
    void actualInnerRadiusChanged();
    void actualOuterRadiusChanged();

protected slots:
    virtual void updateSpinner();

private:
    Q_DISABLE_COPY(BusyIndicator)
    Q_DECLARE_PRIVATE(BusyIndicator)
    QScopedPointer<BusyIndicatorPrivate> const d_ptr;
};

} // namespace widgets
} // namespace maily

#endif // BUSYINDICATOR_H
