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

#include "busyindicator.h"

#include <QConicalGradient>
#include <QPainter>
#include <QPainterPath>
#include <QPixmapCache>

namespace Maily
{
namespace Widgets
{

class BusyIndicatorPrivate
{
public:
    BusyIndicatorPrivate() : m_innerRadius(0.8), m_outerRadius(1.0),
        m_backgroundColor(177, 210, 143, 70),
        m_foregroundColor(119, 183, 83, 255), m_actualInnerRadius(0.0),
        m_actualOuterRadius(0.0), m_cacheKey()
    {
    }

    // User settable properties
    qreal m_innerRadius; // In range (0, m_outerRadius]
    qreal m_outerRadius; // (m_innerRadius, 1]
    QColor m_backgroundColor;
    QColor m_foregroundColor;

    // The calculated size, inner and outer radii
    qreal m_size;
    qreal m_actualInnerRadius;
    qreal m_actualOuterRadius;

    QString m_cacheKey;
};

BusyIndicator::BusyIndicator(QDeclarativeItem* parent) :
    QDeclarativeItem(parent), d_ptr(new BusyIndicatorPrivate())
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    setWidth(16.0);
    setHeight(16.0);

    updateSpinner();

    connect(this, SIGNAL(widthChanged()), SLOT(updateSpinner()));
    connect(this, SIGNAL(heightChanged()), SLOT(updateSpinner()));
}

BusyIndicator::~BusyIndicator()
{
}

void BusyIndicator::setInnerRadius(const qreal& innerRadius)
{
    Q_D(BusyIndicator);
    if (qFuzzyCompare(d->m_innerRadius, innerRadius))
        return;

    d->m_innerRadius = innerRadius;
    updateSpinner();
    emit innerRadiusChanged();
}

qreal BusyIndicator::innerRadius() const
{
    Q_D(const BusyIndicator);
    return d->m_innerRadius;
}

void BusyIndicator::setOuterRadius(const qreal& outerRadius)
{
    Q_D(BusyIndicator);
    if (qFuzzyCompare(d->m_outerRadius, outerRadius))
        return;

    d->m_outerRadius = outerRadius;
    updateSpinner();
    emit outerRadiusChanged();
}

qreal BusyIndicator::outerRadius() const
{
    Q_D(const BusyIndicator);
    return d->m_outerRadius;
}

void BusyIndicator::setBackgroundColor(const QColor& color)
{
    Q_D(BusyIndicator);
    if (d->m_backgroundColor == color)
        return;

    d->m_backgroundColor = color;
    updateSpinner();
    emit backgroundColorChanged();
}

QColor BusyIndicator::backgroundColor() const
{
    Q_D(const BusyIndicator);
    return d->m_backgroundColor;
}

void BusyIndicator::setForegroundColor(const QColor& color)
{
    Q_D(BusyIndicator);
    if (d->m_foregroundColor == color)
        return;

    d->m_foregroundColor = color;
    updateSpinner();
    emit foregroundColorChanged();
}

QColor BusyIndicator::foregroundColor() const
{
    Q_D(const BusyIndicator);
    return d->m_foregroundColor;
}

qreal BusyIndicator::actualInnerRadius() const
{
    Q_D(const BusyIndicator);
    return d->m_actualInnerRadius;
}

qreal BusyIndicator::actualOuterRadius() const
{
    Q_D(const BusyIndicator);
    return d->m_actualOuterRadius;
}

void BusyIndicator::updateSpinner()
{
    Q_D(BusyIndicator);

    // Calculate new inner and outer radius
    d->m_size = qMin(width(), height());
    qreal nCoef = 0.5 * d->m_size;
    d->m_actualInnerRadius = nCoef * d->m_innerRadius;
    d->m_actualOuterRadius = nCoef * d->m_outerRadius;

    // Calculate a new key
    d->m_cacheKey = d->m_backgroundColor.name();
    d->m_cacheKey += "-";
    d->m_cacheKey += d->m_foregroundColor.name();
    d->m_cacheKey += "-";
    d->m_cacheKey += QString::number(d->m_actualOuterRadius);
    d->m_cacheKey += "-";
    d->m_cacheKey += QString::number(d->m_actualInnerRadius);

    emit actualInnerRadiusChanged();
    emit actualOuterRadiusChanged();
}

void BusyIndicator::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_D(BusyIndicator);

    QPixmap pixmap;
    if (!QPixmapCache::find(d->m_cacheKey, pixmap))
    {
        // Set up a convenient path
        QPainterPath path;
        path.setFillRule(Qt::OddEvenFill);
        path.addEllipse(QPointF(d->m_actualOuterRadius, d->m_actualOuterRadius),
                        d->m_actualOuterRadius, d->m_actualOuterRadius);
        path.addEllipse(QPointF(d->m_actualOuterRadius, d->m_actualOuterRadius),
                        d->m_actualInnerRadius, d->m_actualInnerRadius);

        qreal nActualDiameter = 2 * d->m_actualOuterRadius;
        pixmap = QPixmap(nActualDiameter, nActualDiameter);
        pixmap.fill(Qt::transparent);
        QPainter p(&pixmap);

        // Draw the ring background
        p.setPen(Qt::NoPen);
        p.setBrush(d->m_backgroundColor);
        p.setRenderHints(QPainter::Antialiasing);
        p.drawPath(path);

        // Draw the ring foreground
        QConicalGradient gradient(QPointF(d->m_actualOuterRadius,
                                          d->m_actualOuterRadius), 0.0);
        gradient.setColorAt(0.0, Qt::transparent);
        gradient.setColorAt(0.05, d->m_foregroundColor);
        gradient.setColorAt(0.8, Qt::transparent);
        p.setBrush(gradient);
        p.drawPath(path);
        p.end();

        QPixmapCache::insert(d->m_cacheKey, pixmap);
    }

    // Draw pixmap at center of item
    painter->drawPixmap(0.5 * (width() - d->m_size), 0.5 * (height() - d->m_size),
                        pixmap);
}

} // namespace widgets
} // namespace maily
