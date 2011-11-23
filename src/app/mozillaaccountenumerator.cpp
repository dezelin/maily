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

#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>

#include "mozillaaccountenumerator.h"
#include "tools.h"

namespace Maily
{
namespace Services
{

const QString kMozillaISPDBUrlTemplate =
    "http://ispdb.mozillamessaging.com/export_xml/v1.1/%1";

class MozillaAccountEnumeratorPrivate
{
public:
    MozillaAccountEnumeratorPrivate(const QString& domain) :
        m_domain(domain)
    {
    }

    QString m_domain;
    QScopedPointer<QList<ServiceProviderInfo> > m_accounts;
};

MozillaAccountEnumerator::MozillaAccountEnumerator(QObject* parent,
    const QString& domain) : AccountEnumerator(parent),
    d_ptr(new MozillaAccountEnumeratorPrivate(domain))
{
}

MozillaAccountEnumerator::~MozillaAccountEnumerator()
{
}

QList<ServiceProviderInfo>* MozillaAccountEnumerator::enumerateAccounts()
{
    Q_D(MozillaAccountEnumerator);

    d->m_accounts.reset(new QList<ServiceProviderInfo>());

    QEventLoop loop;
    QScopedPointer<QNetworkAccessManager> networkManager(new QNetworkAccessManager);
    connect(networkManager.data(), SIGNAL(finished(QNetworkReply*)), &loop,
        SLOT(quit()));

    QString serviceUrl = kMozillaISPDBUrlTemplate.arg(d->m_domain);
    qDebug() << QString("Getting service description from %1").arg(serviceUrl);
    QNetworkReply* reply = networkManager->get(QNetworkRequest(QUrl(serviceUrl)));

    loop.exec();
    // do something with the reply.

    return d->m_accounts.take();
}

} // namespace Services
} // namespace Maily
