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

#ifndef EMAILSERVICEPROVIDER_H
#define EMAILSERVICEPROVIDER_H

#include <QObject>
#include <QScopedPointer>

#include "emailserviceproviderinfo.h"

namespace Maily
{
namespace Services
{

class EmailServiceProviderPrivate;
class EmailServiceProvider : public QObject
{
    Q_OBJECT

public:
    explicit EmailServiceProvider(QObject *parent = 0,
        EmailServiceProviderInfo* providerInfo = 0);
    virtual ~EmailServiceProvider();

    bool connect();
    bool disconnect();

    void setDummyCertVerifier(bool dummy);

signals:

public slots:

private:
    bool createSession();
    QString serviceTypeString() const;

private:
    Q_DISABLE_COPY(EmailServiceProvider)
    Q_DECLARE_PRIVATE(EmailServiceProvider)
    QScopedPointer<EmailServiceProviderPrivate> d_ptr;
};

} // namespace Services
} // namespace Maily

#endif // EMAILSERVICEPROVIDER_H
