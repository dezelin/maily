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

#include <QDomDocument>
#include <QDomElement>
#include <QEventLoop>
#include <QNetworkAccessManager>

#include "emailserviceproviderinfo.h"
#include "mozillaaccountenumerator.h"
#include "tools.h"

namespace Maily
{
namespace Services
{

const QString kMozillaISPDBClientConfigVersion = "1.1";
const QString kMozillaISPDBUrlTemplate =
    "http://ispdb.mozillamessaging.com/export_xml/v1.1/%1";

const QString kAttributeId = "id";
const QString kAttributeType = "type";
const QString kElementClientConfig = "clientConfig";
const QString kElementEmailProvider = "emailProvider";
const QString kElementDisplayName = "displayName";
const QString kElementDisplayShortName = "displayShortName";
const QString kElementIncomingServer = "incomingServer";
const QString kElementOutgoingServer = "outgoingServer";
const QString kElementHostname = "hostname";
const QString kElementPort = "port";
const QString kElementSocketType = "socketType";
const QString kElementUsername = "username";
const QString kElementAuthentication = "authentication";

const QString kServerTypeImap = "imap";
const QString kServerTypePop3 = "pop3";
const QString kServerTypeSmtp = "smtp";
const QString kServerSocketTypeNone = "none";
const QString kServerSocketTypeSSL = "ssl";
const QString kServerSocketTypeSTARTTLS = "starttls";
const QString kServerSocketTypeTLS = "tls";
const QString kServerAuthenticationTypeCleartext = "password-cleartext";
const QString kServerAuthenticationTypeNone = "none";
const QString kServerAuthenticationTypePlain = "plain";
const QString kServerAuthenticationTypeSecure = "secure";

const QString kDOMElementUndefined = "DOM element is not defined.";

class MozillaAccountEnumeratorPrivate
{
public:
    MozillaAccountEnumeratorPrivate(const QString& domain) :
        m_domain(domain)
    {
    }

    QString m_domain;
    QScopedPointer<QList<ServiceProviderInfo*> > m_accounts;
};

MozillaAccountEnumerator::MozillaAccountEnumerator(QObject* parent,
    const QString& domain) : AccountEnumerator(parent),
    d_ptr(new MozillaAccountEnumeratorPrivate(domain))
{
}

MozillaAccountEnumerator::~MozillaAccountEnumerator()
{
}

QList<ServiceProviderInfo*>* MozillaAccountEnumerator::enumerateAccounts()
{
    Q_D(MozillaAccountEnumerator);

    d->m_accounts.reset(new QList<ServiceProviderInfo*>());

    QEventLoop loop;
    QScopedPointer<QNetworkAccessManager> networkManager(new QNetworkAccessManager);
    connect(networkManager.data(), SIGNAL(finished(QNetworkReply*)), &loop,
        SLOT(quit()));

    QString serviceUrl = kMozillaISPDBUrlTemplate.arg(d->m_domain);
    qLog() << QString("Getting service description from %1").arg(serviceUrl);
    QScopedPointer<QNetworkReply> reply(networkManager->get(QNetworkRequest(
        QUrl(serviceUrl))));

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qLog() << QString("Error: %1").arg(reply->errorString());
        return 0;
    }

    QDomDocument dom;
    dom.setContent(reply.data());

    qLog() << "Service description text:\n" << dom.toString();

    QDomElement root = dom.firstChildElement(kElementClientConfig);
    if (!root.isNull()) {
        QString version = root.attribute("version").trimmed();
        if (version != kMozillaISPDBClientConfigVersion) {
            qLog() << QString("Unsupported client config version %1!").arg(
                version);
            return 0;
        }
    }

    QDomElement emailProvider = root.firstChildElement(kElementEmailProvider);
    QDomElement displayName = emailProvider.firstChildElement(kElementDisplayName);
    QDomElement displayShortName = emailProvider.firstChildElement(kElementDisplayShortName);
    if (emailProvider.isNull() || displayName.isNull()
        || displayShortName.isNull()) {
        qLog() << kDOMElementUndefined;
        return 0;
    }

    QString serverElements[] = { kElementIncomingServer, kElementOutgoingServer };

    for(unsigned int i = 0; i < sizeof(serverElements) / sizeof(serverElements[0]); ++i) {
        QString serverElement = serverElements[i];
        QDomElement server = emailProvider.firstChildElement(serverElement);
        QDomElement hostname = server.firstChildElement(kElementHostname);
        QDomElement port = server.firstChildElement(kElementPort);
        QDomElement socketType = server.firstChildElement(kElementSocketType);
        QDomElement username = server.firstChildElement(kElementUsername);
        QDomElement authentication = server.firstChildElement(kElementAuthentication);
        if (server.isNull() || hostname.isNull() || port.isNull()
            || socketType.isNull() || username.isNull() || authentication.isNull()) {
            qLog() << kDOMElementUndefined;
            break;
        }

        EmailServiceProviderInfo::ServiceTypes serviceType;
        QString serverSocketType = socketType.text().toLower().trimmed();
        QString serverType = server.attribute(kAttributeType).toLower().trimmed();
        if (serverType == kServerTypeImap) {
            serviceType = (serverSocketType == kServerSocketTypeNone)
                ? EmailServiceProviderInfo::IMAP : EmailServiceProviderInfo::IMAPS;
        } else if (serverType == kServerTypePop3) {
            serviceType = (serverSocketType == kServerSocketTypeNone)
                ? EmailServiceProviderInfo::POP3 : EmailServiceProviderInfo::POP3S;
        } else if (serverType == kServerTypeSmtp) {
            serviceType = (serverSocketType == kServerSocketTypeNone)
                ? EmailServiceProviderInfo::SMTP : EmailServiceProviderInfo::SMTPS;
        } else {
            qLog() << QString("Undefined server type %1.").arg(serverType);
            break;
        }

        EmailServiceProviderInfo::AuthenticationTypes authenticationType;
        QString serverAuthType = authentication.text().trimmed();
        if (serverAuthType == kServerAuthenticationTypeCleartext)
            authenticationType = EmailServiceProviderInfo::AuthCleartext;
        else if (serverAuthType == kServerAuthenticationTypePlain)
            authenticationType = EmailServiceProviderInfo::AuthPlain;
        else if (serverAuthType == kServerAuthenticationTypeSecure)
            authenticationType = EmailServiceProviderInfo::AuthSASL;
        else if (serverAuthType == kServerAuthenticationTypeNone)
            authenticationType = EmailServiceProviderInfo::AuthNone;
        else {
            qLog() << QString("Undefined authentication type type %1.").arg(serverAuthType);
            break;
        }

        QScopedPointer<EmailServiceProviderInfo> providerInfo(
            new EmailServiceProviderInfo());
        providerInfo->setDisplayName(displayName.text().trimmed());
        providerInfo->setDisplayShortName(displayShortName.text().trimmed());
        providerInfo->setServiceType(serviceType);
        providerInfo->setAddress(hostname.text().trimmed());
        providerInfo->setPort(port.text().toInt());
        providerInfo->setUsername(username.text().trimmed());
        providerInfo->setAuthenticationType(authenticationType);

        if (serverType == kServerSocketTypeSTARTTLS) {
            providerInfo->setTls(true);
            providerInfo->setTlsRequired(false);
        }

        d->m_accounts->append(providerInfo.take());
    }

    return d->m_accounts.take();
}

} // namespace Services
} // namespace Maily
