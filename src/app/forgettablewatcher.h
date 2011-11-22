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

#ifndef FORGETTABLEWATCHER_H
#define FORGETTABLEWATCHER_H

#include <QFutureWatcher>
#include <QScopedPointer>

namespace Maily
{
namespace Services
{
namespace Tasks
{

class ForgettableWatcherBasePrivate;

class ForgettableWatcherBase : public QObject
{
    Q_OBJECT

public:
    ForgettableWatcherBase(QObject* parent);
    virtual ~ForgettableWatcherBase();

    int progressValue() const;
    int progressMinimum() const;
    int progressMaximum() const;
    QString progressText() const;

    bool isStarted() const;
    bool isFinished() const;
    bool isRunning() const;
    bool isCanceled() const;
    bool isPaused() const;

    void waitForFinished();

    void setPendingResultsLimit(int limit);

Q_SIGNALS:
    void started();
    void finished();
    void canceled();
    void paused();
    void resumed();
    void resultReadyAt(int resultIndex);
    void resultsReadyAt(int beginIndex, int endIndex);
    void progressRangeChanged(int minimum, int maximum);
    void progressValueChanged(int progressValue);
    void progressTextChanged(const QString &progressText);

public Q_SLOTS:
    void cancel();
    void setPaused(bool paused);
    void pause();
    void resume();
    void togglePaused();

protected:
    // called from setFuture() implemented in template sub-classes
    void connectOutputInterface();
    void disconnectOutputInterface(bool pendingAssignment = false);
    void connectForwardedInterface();
    void disconnectForwardedInterface();

private Q_SLOTS:
    void deleteObject();

private:
    // implemented in the template sub-classes
    virtual const QFutureInterfaceBase &futureInterface() const = 0;
    virtual QFutureInterfaceBase &futureInterface() = 0;

private:
    QScopedPointer<ForgettableWatcherBasePrivate> d_ptr;
    Q_DECLARE_PRIVATE(ForgettableWatcherBase)
    Q_DISABLE_COPY(ForgettableWatcherBase)
};

template <typename T>
class ForgettableWatcher : public ForgettableWatcherBase
{
public:
    explicit ForgettableWatcher(QObject *parent = 0) :
        ForgettableWatcherBase(parent)
    {
    }

    void destroy()
    {
        delete this;
    }

    void setFuture(const QFuture<T> &future);
    QFuture<T> future() const
    { return m_future; }

    T result() const { return m_future.result(); }
    T resultAt(int index) const { return m_future.resultAt(index); }

private:

    // Disable allocation in stack
    ~ForgettableWatcher()
    {
        disconnectOutputInterface();
        disconnectForwardedInterface();
    }

    QFuture<T> m_future;
    virtual const QFutureInterfaceBase &futureInterface() const { return m_future.d; }
    virtual QFutureInterfaceBase &futureInterface() { return m_future.d; }
};

template <typename T>
Q_INLINE_TEMPLATE void ForgettableWatcher<T>::setFuture(const QFuture<T> &_future)
{
    if (_future == m_future)
        return;

    connectForwardedInterface();
    disconnectOutputInterface(true);
    m_future = _future;
    connectOutputInterface();
}

} // namespace Tasks
} // namespace Services
} // namespace Maily

#endif // FORGETTABLEWATCHER_H
