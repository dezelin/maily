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

#include "mozillaaccountenumerator.h"

namespace Maily
{
namespace Services
{

namespace Details
{
    struct MozillaAccountEnumeratorPrivate
    {
        MozillaAccountEnumeratorPrivate(const QString& domain) :
            m_domain(domain)
        {

        }

        QString m_domain;
    };
}

MozillaAccountEnumerator::MozillaAccountEnumerator(QObject *parent,
                                                   const QString& domain) :
    AccountEnumerator(parent),
    m_data(new Details::MozillaAccountEnumeratorPrivate(domain))
{
}

QList<ServiceProviderInfo>* MozillaAccountEnumerator::enumerateAccounts() const
{
    sleep(10);
    return new QList<ServiceProviderInfo>();
}

} // namespace Services
} // namespace Maily
