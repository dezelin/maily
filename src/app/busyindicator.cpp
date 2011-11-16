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

BusyIndicator::BusyIndicator(QDeclarativeItem* parent)
    : QDeclarativeItem(parent),
      m_innerRadius(0.8),
      m_outerRadius(1.0),
      m_backgroundColor(177, 210, 143, 70),
      m_foregroundColor(119, 183, 83, 255),
      m_actualInnerRadius(0.0),
      m_actualOuterRadius(0.0),
      m_cacheKey()
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    setWidth(16.0);
    setHeight(16.0);

    updateSpinner();

    connect(this, SIGNAL(widthChanged()), SLOT(updateSpinner()));
    connect(this, SIGNAL(heightChanged()), SLOT(updateSpinner()));
}

void BusyIndicator::setInnerRadius(const qreal& innerRadius)
{
    if (qFuzzyCompare(m_innerRadius, innerRadius))
        return;
    m_innerRadius = innerRadius;
    updateSpinner();
    emit innerRadiusChanged();
}

qreal BusyIndicator::innerRadius() const
{
    return m_innerRadius;
}

void BusyIndicator::setOuterRadius(const qreal& outerRadius)
{
    if (qFuzzyCompare(m_outerRadius, outerRadius))
        return;
    m_outerRadius = outerRadius;
    updateSpinner();
    emit outerRadiusChanged();
}

qreal BusyIndicator::outerRadius() const
{
    return m_outerRadius;
}

void BusyIndicator::setBackgroundColor(const QColor& color)
{
    if (m_backgroundColor == color)
        return;
    m_backgroundColor = color;
    updateSpinner();
    emit backgroundColorChanged();
}

QColor BusyIndicator::backgroundColor() const
{
    return m_backgroundColor;
}

void BusyIndicator::setForegroundColor(const QColor& color)
{
    if (m_foregroundColor == color)
        return;
    m_foregroundColor = color;
    updateSpinner();
    emit foregroundColorChanged();
}

QColor BusyIndicator::foregroundColor() const
{
    return m_foregroundColor;
}

qreal BusyIndicator::actualInnerRadius() const
{
    return m_actualInnerRadius;
}

qreal BusyIndicator::actualOuterRadius() const
{
    return m_actualOuterRadius;
}

void BusyIndicator::updateSpinner()
{
    // Calculate new inner and outer radius
    m_size = qMin(width(), height());
    qreal nCoef = 0.5 * m_size;
    m_actualInnerRadius = nCoef * m_innerRadius;
    m_actualOuterRadius = nCoef * m_outerRadius;

    // Calculate a new key
    m_cacheKey = m_backgroundColor.name();
    m_cacheKey += "-";
    m_cacheKey += m_foregroundColor.name();
    m_cacheKey += "-";
    m_cacheKey += QString::number(m_actualOuterRadius);
    m_cacheKey += "-";
    m_cacheKey += QString::number(m_actualInnerRadius);

    emit actualInnerRadiusChanged();
    emit actualOuterRadiusChanged();
}

void BusyIndicator::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap pixmap;
    if (!QPixmapCache::find(m_cacheKey, pixmap))
    {
        // Set up a convenient path
        QPainterPath path;
        path.setFillRule(Qt::OddEvenFill);
        path.addEllipse(QPointF(m_actualOuterRadius, m_actualOuterRadius),
                        m_actualOuterRadius, m_actualOuterRadius);
        path.addEllipse(QPointF(m_actualOuterRadius, m_actualOuterRadius),
                        m_actualInnerRadius, m_actualInnerRadius);

        qreal nActualDiameter = 2 * m_actualOuterRadius;
        pixmap = QPixmap(nActualDiameter, nActualDiameter);
        pixmap.fill(Qt::transparent);
        QPainter p(&pixmap);

        // Draw the ring background
        p.setPen(Qt::NoPen);
        p.setBrush(m_backgroundColor);
        p.setRenderHints(QPainter::Antialiasing);
        p.drawPath(path);

        // Draw the ring foreground
        QConicalGradient gradient(QPointF(m_actualOuterRadius,
                                          m_actualOuterRadius), 0.0);
        gradient.setColorAt(0.0, Qt::transparent);
        gradient.setColorAt(0.05, m_foregroundColor);
        gradient.setColorAt(0.8, Qt::transparent);
        p.setBrush(gradient);
        p.drawPath(path);
        p.end();

        QPixmapCache::insert(m_cacheKey, pixmap);
    }

    // Draw pixmap at center of item
    painter->drawPixmap(0.5 * (width() - m_size), 0.5 * (height() - m_size),
                        pixmap);
}

} // namespace widgets
} // namespace maily
