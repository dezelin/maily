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

#ifndef MOZILLAACCOUNTENUMERATOR_H
#define MOZILLAACCOUNTENUMERATOR_H

#include <QNetworkReply>
#include <QScopedPointer>

#include "accountenumerator.h"
#include "smartlist.h"

namespace Maily
{
namespace Services
{

using namespace Containers;

class MozillaAccountEnumeratorPrivate;
class MozillaAccountEnumerator : public AccountEnumerator
{
    Q_OBJECT

public:
    MozillaAccountEnumerator(QObject* parent = 0,
        const QString& domain = "");
    virtual ~MozillaAccountEnumerator();

    virtual SmartList<ServiceProviderInfo*>* enumerateAccounts();

private:
    Q_DISABLE_COPY(MozillaAccountEnumerator)
    Q_DECLARE_PRIVATE(MozillaAccountEnumerator)
    QScopedPointer<MozillaAccountEnumeratorPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // MOZILLAACCOUNTENUMERATOR_H
