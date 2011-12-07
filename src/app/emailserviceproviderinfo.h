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

    enum ServiceTypes { POP3 = 1, POP3S = 2, IMAP = 4, IMAPS = 8, SMTP = 16,
        SMTPS = 32, MAILDIR = 64, SENDMAIL = 128 };

    ServiceTypes serviceType() const;
    void setServiceType(ServiceTypes type);

    bool tls() const;
    void setTls(bool tls);

    bool tlsRequired() const;
    void setTlsRequired(bool tlsRequired);

    const QString& rootPath() const;
    void setRootPath(const QString& rootPath);

    const QString& sendmailBinPath() const;
    void setSendmailBinPath(const QString& path);

    enum AuthenticationTypes { AuthAuto = 1, AuthNone = 2, AuthCleartext = 4,
        AuthPlain = 8, AuthSASL = 16, AuthAPOP = 32, AuthKerberos = 64,
        AuthNTLM = 128 };

    AuthenticationTypes authenticationType() const;
    void setAuthenticationType(AuthenticationTypes type);

    bool authenication() const;
    bool apop() const;
    bool apopFallback() const;
    bool cleartext() const;
    bool cleartextFallback() const;
    bool kerberos() const;
    bool kerberosFallback() const;
    bool ntlm() const;
    bool ntlmFallback() const;
    bool plain() const;
    bool plainFallback() const;
    bool sasl() const;
    bool saslFallback() const;
    bool smtpAuthentication() const;

private:
    Q_DECLARE_PRIVATE(EmailServiceProviderInfo)
    QScopedPointer<EmailServiceProviderInfoPrivate> d_ptr;
};

inline EmailServiceProviderInfo::AuthenticationTypes operator| (
    EmailServiceProviderInfo::AuthenticationTypes a,
    EmailServiceProviderInfo::AuthenticationTypes b)
{
    return static_cast<EmailServiceProviderInfo::AuthenticationTypes>(
        static_cast<int>(a) | static_cast<int>(b));
}

inline EmailServiceProviderInfo::ServiceTypes operator| (
    EmailServiceProviderInfo::ServiceTypes a,
    EmailServiceProviderInfo::ServiceTypes b)
{
    return static_cast<EmailServiceProviderInfo::ServiceTypes>(
        static_cast<int>(a) | static_cast<int>(b));
}

} // namespace Services
} // namespace Maily

#endif // EMAILSERVICEPROVIDERINFO_H
