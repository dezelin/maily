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

#include "forgettablewatcher.h"

namespace Maily
{
namespace Services
{
namespace Tasks
{

class ForgettableWatcherBasePrivate : public QFutureWatcherBase
{
    //Q_OBJECT

public:

    explicit ForgettableWatcherBasePrivate(ForgettableWatcherBase *parent = 0);

    // called from setFuture() implemented in template sub-classes
    void connectOutputInterface();
    void disconnectOutputInterface(bool pendingAssignment = false);

private:
    // implemented in the template sub-classes
    virtual const QFutureInterfaceBase& futureInterface() const;
    virtual QFutureInterfaceBase& futureInterface();

private:
    ForgettableWatcherBase* const q_ptr;
    Q_DECLARE_PUBLIC(ForgettableWatcherBase)
    Q_DISABLE_COPY(ForgettableWatcherBasePrivate)
};

ForgettableWatcherBasePrivate::ForgettableWatcherBasePrivate(
    ForgettableWatcherBase *parent) : QFutureWatcherBase(parent), q_ptr(parent)
{
}

const QFutureInterfaceBase& ForgettableWatcherBasePrivate::futureInterface() const
{
    Q_Q(const ForgettableWatcherBase);
    return q->futureInterface();
}

void ForgettableWatcherBasePrivate::connectOutputInterface()
{
    QFutureWatcherBase::connectOutputInterface();
}

void ForgettableWatcherBasePrivate::disconnectOutputInterface(bool pendingAssignment)
{
    QFutureWatcherBase::disconnectOutputInterface(pendingAssignment);
}

QFutureInterfaceBase& ForgettableWatcherBasePrivate::futureInterface()
{
    Q_Q(ForgettableWatcherBase);
    return q->futureInterface();
}

ForgettableWatcherBase::ForgettableWatcherBase(QObject *parent) :
    QObject(parent), d_ptr(new ForgettableWatcherBasePrivate(this))
{
}

ForgettableWatcherBase::~ForgettableWatcherBase()
{
}

int ForgettableWatcherBase::progressValue() const
{
    Q_D(const ForgettableWatcherBase);
    return d->progressValue();
}

int ForgettableWatcherBase::progressMinimum() const
{
    Q_D(const ForgettableWatcherBase);
    return d->progressMinimum();
}

int ForgettableWatcherBase::progressMaximum() const
{
    Q_D(const ForgettableWatcherBase);
    return d->progressMaximum();
}

QString ForgettableWatcherBase::progressText() const
{
    Q_D(const ForgettableWatcherBase);
    return d->progressText();
}

bool ForgettableWatcherBase::isStarted() const
{
    Q_D(const ForgettableWatcherBase);
    return d->isStarted();
}

bool ForgettableWatcherBase::isFinished() const
{
    Q_D(const ForgettableWatcherBase);
    return d->isFinished();
}

bool ForgettableWatcherBase::isRunning() const
{
    Q_D(const ForgettableWatcherBase);
    return d->isRunning();
}

bool ForgettableWatcherBase::isCanceled() const
{
    Q_D(const ForgettableWatcherBase);
    return d->isCanceled();
}

bool ForgettableWatcherBase::isPaused() const
{
    Q_D(const ForgettableWatcherBase);
    return d->isPaused();
}

void ForgettableWatcherBase::waitForFinished()
{
    Q_D(ForgettableWatcherBase);
    d->waitForFinished();
}

void ForgettableWatcherBase::setPendingResultsLimit(int limit)
{
    Q_D(ForgettableWatcherBase);
    d->setPendingResultsLimit(limit);
}

void ForgettableWatcherBase::cancel()
{
    Q_D(ForgettableWatcherBase);
    d->cancel();
}

void ForgettableWatcherBase::setPaused(bool paused)
{
    Q_D(ForgettableWatcherBase);
    d->setPaused(paused);
}

void ForgettableWatcherBase::pause()
{
    Q_D(ForgettableWatcherBase);
    d->pause();
}

void ForgettableWatcherBase::resume()
{
    Q_D(ForgettableWatcherBase);
    d->resume();
}

void ForgettableWatcherBase::togglePaused()
{
    Q_D(ForgettableWatcherBase);
    d->togglePaused();
}

void ForgettableWatcherBase::connectOutputInterface()
{
    Q_D(ForgettableWatcherBase);
    d->connectOutputInterface();
}

void ForgettableWatcherBase::disconnectOutputInterface(bool pendingAssignment)
{
    Q_D(ForgettableWatcherBase);
    d->disconnectOutputInterface(pendingAssignment);
}

void ForgettableWatcherBase::connectForwardedInterface()
{
    Q_D(ForgettableWatcherBase);
    connect(d, SIGNAL(started()), this, SIGNAL(started()));
    connect(d, SIGNAL(finished()), this, SLOT(deleteObject()));
    connect(d, SIGNAL(canceled()), this, SIGNAL(canceled()));
    connect(d, SIGNAL(paused()), this, SIGNAL(paused()));
    connect(d, SIGNAL(resumed()), this, SIGNAL(resumed()));
    connect(d, SIGNAL(resultReadyAt(int)), this, SIGNAL(resultReadyAt(int)));
    connect(d, SIGNAL(resultsReadyAt(int, int)), this, SIGNAL(resultsReadyAt(int, int)));
    connect(d, SIGNAL(progressRangeChanged(int, int)), this, SIGNAL(progressRangeChanged(int, int)));
    connect(d, SIGNAL(progressValueChanged(int)), this, SIGNAL(progressValueChanged(int)));
    connect(d, SIGNAL(progressTextChanged(const QString&)), this, SIGNAL(progressTextChanged(const QString&)));
}

void ForgettableWatcherBase::disconnectForwardedInterface()
{
    Q_D(ForgettableWatcherBase);
    d->disconnect(this);
}

void ForgettableWatcherBase::deleteObject()
{
    emit finished();
    delete this;
}

} // namespace Tasks
} // namespace Services
} // namespace Maily
