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

#ifndef EMAILSERVICEPROVIDERINFO_H
#define EMAILSERVICEPROVIDERINFO_H

#include "serviceproviderinfo.h"

namespace Maily
{
namespace Services
{

namespace Details
{
    struct EmailServiceProviderInfoPrivate;
}

class EmailServiceProviderInfo : public ServiceProviderInfo
{
    Q_OBJECT
    Q_ENUMS(ServiceType)
    Q_PROPERTY(ServiceType serviceType READ serviceType WRITE setServiceType)
    Q_PROPERTY(bool sasl READ sasl WRITE setSasl)
    Q_PROPERTY(bool saslFallback READ saslFallback WRITE setSaslFallback)
    Q_PROPERTY(bool tls READ tls WRITE setTls)
    Q_PROPERTY(bool tlsRequired READ tlsRequired WRITE setTlsRequired)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath)
    Q_PROPERTY(bool apop READ apop WRITE setApop)
    Q_PROPERTY(bool apopFallback READ apopFallback WRITE setApopFallback)

public:
    explicit EmailServiceProviderInfo(QObject *parent = 0);

    enum ServiceType { POP3, POP3S, IMAP, IMAPS, SMTP, SMTPS, MAILDIR, SENDMAIL };

    ServiceType serviceType() const;
    void setServiceType(ServiceType serviceType);

    bool sasl() const;
    void setSasl(bool sasl);

    bool saslFallback() const;
    void setSaslFallback(bool saslFallback);

    bool tls() const;
    void setTls(bool tls);

    bool tlsRequired() const;
    void setTlsRequired(bool tlsRequired);

    const QString& rootPath() const;
    void setRootPath(const QString& rootPath);

    bool apop() const;
    void setApop(bool apop);

    bool apopFallback() const;
    void setApopFallback(bool apopFallback);

signals:

public slots:

private:
    Details::EmailServiceProviderInfoPrivate* m_data;
};

} // namespace Services
} // namespace Maily

#endif // EMAILSERVICEPROVIDERINFO_H
