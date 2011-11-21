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

namespace Maily
{
namespace Services
{
namespace Tasks
{

class ForgettableWatcherBase : public QFutureWatcherBase
{
    Q_OBJECT
    //Q_DECLARE_PRIVATE(ForgettableWatcherBase)

public:
    ForgettableWatcherBase(QObject* parent);

private slots:

    void finish();
};

template <typename T>
class ForgettableWatcher : public ForgettableWatcherBase
{
public:
    explicit ForgettableWatcher(QObject *parent = 0) :
        ForgettableWatcherBase(parent)
    {
    }

    ~ForgettableWatcher()
    {
        disconnectOutputInterface();
    }

    void setFuture(const QFuture<T> &future);
    QFuture<T> future() const
    { return m_future; }

    T result() const { return m_future.result(); }
    T resultAt(int index) const { return m_future.resultAt(index); }

private:
    QFuture<T> m_future;
    const QFutureInterfaceBase &futureInterface() const { return m_future.d; }
    QFutureInterfaceBase &futureInterface() { return m_future.d; }
};

template <typename T>
Q_INLINE_TEMPLATE void ForgettableWatcher<T>::setFuture(const QFuture<T> &_future)
{
    if (_future == m_future)
        return;

    disconnectOutputInterface(true);
    m_future = _future;
    connectOutputInterface();
}

} // namespace Tasks
} // namespace Services
} // namespace Maily

#endif // FORGETTABLEWATCHER_H
