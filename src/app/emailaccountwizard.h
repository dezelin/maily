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

#ifndef EMAILACCOUNTWIZARD_H
#define EMAILACCOUNTWIZARD_H

#include <QList>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QWizard>
#include <QWizardPage>

#include "accountenumerator.h"

namespace Maily
{
namespace Wizards
{

using namespace Services;

namespace Pages
{

class EmailAccountWizardIntroPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardIntroPage(QWidget* parent = 0);
};

class EmailAccountWizardAccountPagePrivate;
class EmailAccountWizardAccountPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardAccountPage(QWidget* parent = 0);
    virtual ~EmailAccountWizardAccountPage();

    virtual void cleanupPage();
    virtual int nextId() const;
    virtual bool validatePage();

private slots:
    void enumerationFinished();

private:
    void disableButtons();
    void enableButtons();
    void next();
    void startBusyIndicator();
    void stopBusyIndicator();

    QList<ServiceProviderInfo*>* enumerateServiceProviders(
        const QString& domainName) const;

private:

    Q_DISABLE_COPY(EmailAccountWizardAccountPage)
    Q_DECLARE_PRIVATE(EmailAccountWizardAccountPage)
    QScopedPointer<EmailAccountWizardAccountPagePrivate> d_ptr;
};

class EmailAccountWizardIncomingServerPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardIncomingServerPage(QWidget* parent = 0);
};

class EmailAccountWizardOutgoingServerPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardOutgoingServerPage(QWidget* parent = 0);
};

class EmailAccountWizardFinishedPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardFinishedPage(QWidget* parent = 0);
};

} // namespace Pages


class EmailAccountWizardPrivate;
class EmailAccountWizard : public QWizard
{
    Q_OBJECT

public:
    explicit EmailAccountWizard(QWidget *parent = 0);
    virtual ~EmailAccountWizard();

signals:

public slots:

private:
    Q_DISABLE_COPY(EmailAccountWizard)
    Q_DECLARE_PRIVATE(EmailAccountWizard)
    QScopedPointer<EmailAccountWizardPrivate> d_ptr;

    QList<ServiceProviderInfo*>* getResult() const;
    void adoptResult(QList<ServiceProviderInfo*>* result);

    friend class Pages::EmailAccountWizardAccountPage;
};


} // namespace Wizards
} // namespace Maily

#endif // EMAILACCOUNTWIZARD_H
