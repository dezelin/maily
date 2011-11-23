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

    QScopedPointer<QNetworkAccessManager> networkManager(new QNetworkAccessManager);
    connect(networkManager.data(), SIGNAL(finished(QNetworkReply*)), this,
        SLOT(finishedReply(QNetworkReply*)));

    QString serviceUrl = kMozillaISPDBUrlTemplate.arg(d->m_domain);
    qDebug() << QString("Getting service description from %1").arg(serviceUrl);
    networkManager->get(QNetworkRequest(QUrl(serviceUrl)));

    QEventLoop loop;
    loop.exec();

    return d->m_accounts.take();
}

void MozillaAccountEnumerator::finishedReply(QNetworkReply *reply)
{
    Q_D(MozillaAccountEnumerator);
    Q_ASSERT(reply);
    if (!reply)
        return;

    //reply->readAll()
}

} // namespace Services
} // namespace Maily
