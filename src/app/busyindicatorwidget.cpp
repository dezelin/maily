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
#include "busyindicatorwidget.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimeLine>
#include <QVBoxLayout>


namespace Maily
{
namespace Widgets
{

struct BusyIndicatorWidgetPrivate
{
    BusyIndicatorWidgetPrivate() : m_busyIndicator(0), m_scene(0),
        m_timeline(0)
    {
    }

    ~BusyIndicatorWidgetPrivate()
    {
        delete m_busyIndicator;
        delete m_scene;
        delete m_timeline;
    }

    BusyIndicator* m_busyIndicator;
    QGraphicsScene* m_scene;
    QTimeLine* m_timeline;
};

BusyIndicatorWidget::BusyIndicatorWidget(QWidget *parent) :
QWidget(parent), d_ptr(new BusyIndicatorWidgetPrivate())
{
    Q_D(BusyIndicatorWidget);

    QLayout* layout = new QVBoxLayout();

    d->m_busyIndicator = new BusyIndicator();
    d->m_scene = new QGraphicsScene(this);
    d->m_scene->addItem(dynamic_cast<QGraphicsItem*>(d->m_busyIndicator));
    d->m_scene->setBackgroundBrush(palette().background());
    QGraphicsView* view = new QGraphicsView(d->m_scene, this);
    view->setFrameStyle(QFrame::NoFrame);
    view->setViewport(parent);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->show();

    layout->addWidget(view);
    setLayout(layout);

    d->m_timeline = new QTimeLine(1000, this);
    d->m_timeline->setLoopCount(0);
    d->m_timeline->setFrameRange(0, 36);

    connect(d->m_timeline, SIGNAL(frameChanged(int)), this,
    SLOT(rotateSpinner(int)));
}

BusyIndicatorWidget::~BusyIndicatorWidget()
{
}

void BusyIndicatorWidget::resume()
{
    Q_D(BusyIndicatorWidget);
    d->m_timeline->resume();
}

void BusyIndicatorWidget::start()
{
    Q_D(BusyIndicatorWidget);
    d->m_timeline->start();
}

void BusyIndicatorWidget::stop()
{
    Q_D(BusyIndicatorWidget);
    d->m_timeline->stop();
}

void BusyIndicatorWidget::rotateSpinner(int value)
{
    Q_D(BusyIndicatorWidget);
    qreal transx = d->m_busyIndicator->actualOuterRadius();
    d->m_busyIndicator->setTransform(QTransform().translate(
    transx, transx).rotate(value * 10).translate(-1 * transx, -1 * transx));
}

} // namespace widgets
} // namespace maily
