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

#include <QScopedPointer>

#include "serviceproviderinfo.h"

namespace Maily
{
namespace Services
{


class EmailServiceProviderInfoPrivate;
class EmailServiceProviderInfo : public ServiceProviderInfo
{
public:
    EmailServiceProviderInfo();
    virtual ~EmailServiceProviderInfo();

    EmailServiceProviderInfo(const EmailServiceProviderInfo& providerInfo);

    EmailServiceProviderInfo& operator =(
        const EmailServiceProviderInfo& providerInfo);

    const EmailServiceProviderInfo& operator =(
        const EmailServiceProviderInfo& providerInfo) const;

    void swap(EmailServiceProviderInfo& providerInfo);

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

private:
    Q_DECLARE_PRIVATE(EmailServiceProviderInfo)
    QScopedPointer<EmailServiceProviderInfoPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // EMAILSERVICEPROVIDERINFO_H
