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

namespace maily
{
namespace widgets
{

namespace details
{

struct BusyIndicatorWidgetPrivate
{
  BusyIndicatorWidgetPrivate() : running_(false), busy_indicator_(0), scene_(0),
    timeline_(0)
  {
  }

  bool running_;
  BusyIndicator* busy_indicator_;
  QGraphicsScene* scene_;
  QTimeLine* timeline_;
};

} // namespace details

BusyIndicatorWidget::BusyIndicatorWidget(QWidget *parent) :
  QWidget(parent), data_(new details::BusyIndicatorWidgetPrivate())
{
  QLayout* layout = new QVBoxLayout();

  data_->busy_indicator_ = new BusyIndicator();
  data_->scene_ = new QGraphicsScene(this);
  data_->scene_->addItem(dynamic_cast<QGraphicsItem*>(data_->busy_indicator_));
  QGraphicsView* view = new QGraphicsView(data_->scene_, this);
  view->setViewport(parent);
  view->setMinimumHeight(50);
  view->show();

  layout->addWidget(view);
  setLayout(layout);

  data_->timeline_ = new QTimeLine(1000, this);
  data_->timeline_->setLoopCount(0);
  data_->timeline_->setFrameRange(0, 36);

  connect(data_->timeline_, SIGNAL(frameChanged(int)), this,
          SLOT(rotateSpinner(int)));
}

BusyIndicatorWidget::~BusyIndicatorWidget()
{
  delete data_;
}

void BusyIndicatorWidget::start()
{
  data_->running_ = true;
}

void BusyIndicatorWidget::stop()
{
  data_->running_ = false;
}

void BusyIndicatorWidget::rotateSpinner(int value)
{
  if (!data_->running_)
    return;

  qreal transx = data_->busy_indicator_->actualOuterRadius();
  data_->busy_indicator_->setTransform(QTransform().translate(
    transx, transx).rotate(value * 10).translate(-1 * transx, -1 * transx));
}

} // namespace widgets
} // namespace maily
