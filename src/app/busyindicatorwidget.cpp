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

namespace details
{

struct BusyIndicatorWidgetPrivate
{
  BusyIndicatorWidgetPrivate() : m_busyIndicator(0), m_scene(0),
    m_timeline(0)
  {
  }

  BusyIndicator* m_busyIndicator;
  QGraphicsScene* m_scene;
  QTimeLine* m_timeline;
};

} // namespace details

BusyIndicatorWidget::BusyIndicatorWidget(QWidget *parent) :
  QWidget(parent), m_data(new details::BusyIndicatorWidgetPrivate())
{
  QLayout* layout = new QVBoxLayout();

  m_data->m_busyIndicator = new BusyIndicator();
  m_data->m_scene = new QGraphicsScene(this);
  m_data->m_scene->addItem(dynamic_cast<QGraphicsItem*>(m_data->m_busyIndicator));
  m_data->m_scene->setBackgroundBrush(palette().background());
  QGraphicsView* view = new QGraphicsView(m_data->m_scene, this);
  view->setFrameStyle(QFrame::NoFrame);
  view->setViewport(parent);
  view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  view->show();

  layout->addWidget(view);
  setLayout(layout);

  m_data->m_timeline = new QTimeLine(1000, this);
  m_data->m_timeline->setLoopCount(0);
  m_data->m_timeline->setFrameRange(0, 36);

  connect(m_data->m_timeline, SIGNAL(frameChanged(int)), this,
          SLOT(rotateSpinner(int)));
}

BusyIndicatorWidget::~BusyIndicatorWidget()
{
  delete m_data;
}

void BusyIndicatorWidget::resume()
{
  m_data->m_timeline->resume();
}

void BusyIndicatorWidget::start()
{
  m_data->m_timeline->start();
}

void BusyIndicatorWidget::stop()
{
  m_data->m_timeline->stop();
}

void BusyIndicatorWidget::rotateSpinner(int value)
{
  qreal transx = m_data->m_busyIndicator->actualOuterRadius();
  m_data->m_busyIndicator->setTransform(QTransform().translate(
    transx, transx).rotate(value * 10).translate(-1 * transx, -1 * transx));
}

} // namespace widgets
} // namespace maily
