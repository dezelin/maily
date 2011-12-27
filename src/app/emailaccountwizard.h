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
#include "emailserviceproviderinfo.h"

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
    void startFutureWatcher();

    QList<ServiceProviderInfo*>* enumerateServiceProviders(
        const QString& domainName) const;

private:

    Q_DISABLE_COPY(EmailAccountWizardAccountPage)
    Q_DECLARE_PRIVATE(EmailAccountWizardAccountPage)
    QScopedPointer<EmailAccountWizardAccountPagePrivate> d_ptr;
};

class EmailAccountWizardIncomingServerPagePrivate;
class EmailAccountWizardIncomingServerPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardIncomingServerPage(QWidget* parent = 0);
    virtual ~EmailAccountWizardIncomingServerPage();

    virtual void initializePage();

public slots:
    void testButtonClicked(int which);

private slots:
    void changed();
    void completeChanged();
    void incomingServerTypeIndexChanged(int index);
    void incomingSSLIndexChanged(int index);
    void testFinished();

private:
    bool test();

private:
    Q_DISABLE_COPY(EmailAccountWizardIncomingServerPage)
    Q_DECLARE_PRIVATE(EmailAccountWizardIncomingServerPage)
    QScopedPointer<EmailAccountWizardIncomingServerPagePrivate> d_ptr;
};

class EmailAccountWizardOutgoingServerPagePrivate;
class EmailAccountWizardOutgoingServerPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit EmailAccountWizardOutgoingServerPage(QWidget* parent = 0);
    virtual ~EmailAccountWizardOutgoingServerPage();

    virtual void initializePage();

public slots:
    void testButtonClicked(int which);

private slots:
    void changed();
    void completeChanged();
    void incomingServerTypeIndexChanged(int index);
    void incomingSSLIndexChanged(int index);
    void incomingAuthIndexChanged(int index);
    void testFinished();

private:
    bool test();

private:
    Q_DISABLE_COPY(EmailAccountWizardOutgoingServerPage)
    Q_DECLARE_PRIVATE(EmailAccountWizardOutgoingServerPage)
    QScopedPointer<EmailAccountWizardOutgoingServerPagePrivate> d_ptr;
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
    Q_ENUMS(Pages)

public:
    explicit EmailAccountWizard(QWidget *parent = 0);
    virtual ~EmailAccountWizard();

    enum Pages { PageIntro = 0, PageEmailAccount, PageEmailIncomingServer,
        PageEmailOutgoingServer, PageFinished };

protected:
    virtual void done(int result);

private slots:
    void currentIdChanged(int id);

private:
    Q_DISABLE_COPY(EmailAccountWizard)
    Q_DECLARE_PRIVATE(EmailAccountWizard)
    QScopedPointer<EmailAccountWizardPrivate> d_ptr;

    QList<ServiceProviderInfo*>* getResult();
    QList<ServiceProviderInfo*>* getResultFromFields();
    ServiceProviderInfo* getResultFromIncomingPage();
    ServiceProviderInfo* getResultFromOutgoingPage();
    void adoptResult(QList<ServiceProviderInfo*>* result);

    enum TestButtonStyles { TestButtonDisabled, TestButtonRed, TestButtonBlue };
    void updateTestButton(TestButtonStyles style);

    void storeProviders(QList<ServiceProviderInfo*>* providers);

    friend class Pages::EmailAccountWizardAccountPage;
    friend class Pages::EmailAccountWizardIncomingServerPage;
    friend class Pages::EmailAccountWizardOutgoingServerPage;
};


} // namespace Wizards
} // namespace Maily

#endif // EMAILACCOUNTWIZARD_H
