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

#ifndef EMAILACCOUNTMODEL_H
#define EMAILACCOUNTMODEL_H

#include "accountmodel.h"

namespace maily {
namespace models {

namespace details {

typedef enum {
    IMAP = 0,
    IMAPS,
    POP3,
    POP3S,
    SMTP,
    SMTPS,
    MAILDIR,
    SENDMAIL
} ServerType;

struct EmailAccountModelPrivate;
} // namespace details

class EmailAccountModel : public AccountModel
{
    Q_OBJECT

public:

    typedef details::ServerType ServerType;

    explicit EmailAccountModel(QObject *parent = 0);
    virtual ~EmailAccountModel();

    //
    // Getters and setters
    //

    ServerType serverType() const;
    void setServerType(ServerType serverType);

    bool sasl() const;
    void setSasl(bool sasl);

    bool saslFallback() const;
    void setSaslFallback(bool saslFallback);

    const QString& username() const;
    void setUsername(const QString& username);

    const QString& password() const;
    void setPassword(const QString& password);

    bool tls() const;
    void setTls(bool tls);

    bool tlsRequired() const;
    void setTlsRequired(bool tlsRequired);

    const QString& address() const;
    void setAddress(const QString& address);

    int port() const;
    void setPort(int port);

    const QString& rootPath() const;
    void setRootPath(const QString& rootPath);

    bool apop() const;
    void setApop(bool apop);

    bool apopFallback() const;
    void setApopFallback(bool apopFallback);

    bool needAuthentication() const;
    void setNeedAuthentication(bool needAuthentication);

    const QString& sendmailBinPath() const;
    void setSendmailBinPath(const QString& filePath);

    //
    // Overrides
    //

	virtual bool load(const QString& filePath);
	virtual bool save();

protected:

	//
	// Overrides
	//
	virtual bool createTables();

private:
	details::EmailAccountModelPrivate *m_d;
};


} // namespace models
} // namespace maily

#endif // EMAILACCOUNTMODEL_H
