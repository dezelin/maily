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

#include <QtCore>

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWizardPage>

#include "accountmanagerfactory.h"
#include "busyindicatorwidget.h"
#include "customeditline.h"
#include "forgettablewatcher.h"
#include "emailaccountwizard.h"
#include "emailvalidator.h"
#include "mozillaaccountenumerator.h"
#include "tools.h"

namespace Maily
{
namespace Wizards
{

using namespace Maily::Services::Tasks;
using namespace Maily::Widgets::Validators;

const int kPageIdIntro = 0;
const int kPageIdEmailAccount = 1;
const int kPageIdEmailIncomingServer = 2;
const int kPageIdEmailOutgoingServer = 3;
const int kPageIdFinished = 4;

const QString kBusyLayoutObjectName = "busyLayoutObject";

const QString kFieldFullName = "fullName*";
const QString kFieldEmailAddress = "emailAddress*";
const QString kFieldPassword = "password";
const QString kFieldSavePassword = "savePassword";
const QString kFieldIncomingServerUsername = "incommingServerUsername*";
const QString kFieldIncomingServerPassword = "incommingServerPassword*";
const QString kFieldIncomingServerType = "incommingServerType";
const QString kFieldIncomingServerHostname = "incommingServerHostname*";
const QString kFieldIncomingServerPort = "incommingServerPort";
const QString kFieldIncomingServerSSL = "incommingServerSSL";
const QString kFieldIncomingServerAuth = "incommingServerAuth";
const QString kFieldOutgoingServerUsername = "outgoingServerUsername*";
const QString kFieldOutgoingServerPassword = "outgoingServerPassword*";
const QString kFieldOutgoingServerType = "outgoingServerType";
const QString kFieldOutgoingServerHostname = "outgoingServerHostname*";
const QString kFieldOutgoingServerPort = "outgoingServerPort";
const QString kFieldOutgoingServerSSL = "outgoingServerSSL";
const QString kFieldOutgoingServerAuth = "outgoingServerAuth";


namespace Pages
{

EmailAccountWizardIntroPage::EmailAccountWizardIntroPage(QWidget* parent) :
    QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    QLabel* label = new QLabel(tr("This wizard will help you setup a new email "
                                  "account"));
    label->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
}

typedef ForgettableWatcher<QList<ServiceProviderInfo*>*>
    ForgettableWatcherType;

class EmailAccountWizardAccountPagePrivate
{
public:
    EmailAccountWizardAccountPagePrivate() :
        m_futureStarted(false), m_futureWatcher(0),
        m_emailValidator(new EmailValidator())
    {
    }

    mutable bool m_futureStarted;
    mutable ForgettableWatcherType* m_futureWatcher;
    QScopedPointer<EmailValidator> m_emailValidator;
};

EmailAccountWizardAccountPage::EmailAccountWizardAccountPage(QWidget* parent) :
    QWizardPage(parent),
    d_ptr(new EmailAccountWizardAccountPagePrivate())
{
    Q_D(EmailAccountWizardAccountPage);

    setTitle(tr("Email account user details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* userFullNameLabel = new QLabel(tr("Your full name:"));
    Widgets::CustomEditLine* userFullNameEditLine =
        new Widgets::CustomEditLine();
    userFullNameEditLine->setEmptyMessage(tr("Full name"));
    registerField(kFieldFullName, userFullNameEditLine);

    QLabel* emailAddressLabel = new QLabel(tr("Email address:"));
    Widgets::CustomEditLine* emailAddressEditLine =
        new Widgets::CustomEditLine();
    emailAddressEditLine->setEmptyMessage(tr("Email address"));
    emailAddressEditLine->setValidator(d->m_emailValidator.data());
    registerField(kFieldEmailAddress, emailAddressEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    Widgets::CustomEditLine* passwordEditLine = new Widgets::CustomEditLine();
    passwordEditLine->setEmptyMessage(tr("Password"));
    passwordEditLine->setEchoMode(QLineEdit::Password);
    registerField(kFieldPassword, passwordEditLine);

    QCheckBox* savePasswordCheckBox = new QCheckBox(tr("Save password"));
    registerField(kFieldSavePassword, savePasswordCheckBox);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(userFullNameLabel, 0, 0);
    layout->addWidget(userFullNameEditLine, 0, 1);
    layout->addWidget(emailAddressLabel, 1, 0);
    layout->addWidget(emailAddressEditLine, 1, 1);
    layout->addWidget(passwordLabel, 2, 0);
    layout->addWidget(passwordEditLine, 2, 1);
    layout->addItem(new QSpacerItem(50, 20), 3, 0, 1, -1);
    layout->addWidget(savePasswordCheckBox, 4, 0);
    setLayout(layout);
}

EmailAccountWizardAccountPage::~EmailAccountWizardAccountPage()
{
}

void EmailAccountWizardAccountPage::cleanupPage()
{
    Q_D(EmailAccountWizardAccountPage);

    bool started = d->m_futureStarted;
    if (started) {
        d->m_futureStarted = false;
        d->m_futureWatcher = 0;
        stopBusyIndicator();
    }
}

int EmailAccountWizardAccountPage::nextId() const
{
    Q_D(const EmailAccountWizardAccountPage);

    bool started = d->m_futureStarted;
    if (!started)
        return kPageIdEmailIncomingServer;

    d->m_futureStarted = false; // we will proceed to the next page

    Q_ASSERT(d->m_futureWatcher);
    if (!d->m_futureWatcher)
        return kPageIdEmailIncomingServer;

    bool foundProvider = !d->m_futureWatcher->result()->isEmpty();
    if (foundProvider) {
        d->m_futureWatcher = 0;
        return kPageIdFinished;
    }

    return kPageIdEmailIncomingServer;
}

bool EmailAccountWizardAccountPage::validatePage()
{
    Q_D(EmailAccountWizardAccountPage);

    bool started = d->m_futureStarted;
    bool finished = (d->m_futureWatcher) ? d->m_futureWatcher->isFinished()
        : false;
    if (started && finished)
        return true;

    startBusyIndicator();
    disableButtons();

    QFuture<QList<ServiceProviderInfo*>*> future = QtConcurrent::run(
        this, &EmailAccountWizardAccountPage::enumerateServiceProviders,
            QString("gmail.com"));

    ForgettableWatcherType* futureWatcher = new ForgettableWatcherType();
    connect(futureWatcher, SIGNAL(finished()), this, SLOT(enumerationFinished()));
    futureWatcher->setFuture(future);

    d->m_futureWatcher = futureWatcher;
    d->m_futureStarted = true;

    // FutureWatcher will call enumerationFinished() when finished
    // so return here false and stop proceeding to the next page temporarely.
    return false;
}

void EmailAccountWizardAccountPage::disableButtons()
{
    QWizard* w = wizard();
    Q_ASSERT(w);
    if (!w)
        return;

    QAbstractButton* nextButton = w->button(QWizard::NextButton);
    Q_ASSERT(nextButton);
    if (!nextButton)
        return;

    nextButton->setEnabled(false);
}

void EmailAccountWizardAccountPage::enableButtons()
{
    QWizard* w = wizard();
    Q_ASSERT(w);
    if (!w)
        return;

    QAbstractButton* nextButton = w->button(QWizard::NextButton);
    Q_ASSERT(nextButton);
    if (!nextButton)
        return;

    nextButton->setEnabled(true);
}

void EmailAccountWizardAccountPage::next()
{
    QWizard* w = wizard();
    Q_ASSERT(w);
    if (!w)
        return;

    w->next();
}

void EmailAccountWizardAccountPage::startBusyIndicator()
{
    QGridLayout* l = dynamic_cast<QGridLayout*>(layout());
    Q_ASSERT(l);
    if (!l)
        return;

    QLabel* busyLabel = new QLabel(tr("<b>Checking the online database...</b>"));
    Widgets::BusyIndicatorWidget* busyIndicator =
            new Widgets::BusyIndicatorWidget();

    QHBoxLayout* busyLayout = new QHBoxLayout();
    busyLayout->setObjectName(kBusyLayoutObjectName);
    busyLayout->addWidget(busyLabel, Qt::AlignCenter);
    busyLayout->addWidget(busyIndicator, Qt::AlignRight);
    l->addLayout(busyLayout, l->rowCount() + 1, 0, 1, -1);

    busyIndicator->start();
}

void EmailAccountWizardAccountPage::stopBusyIndicator()
{
    QGridLayout* l = dynamic_cast<QGridLayout*>(layout());
    Q_ASSERT(l);
    if (!l)
        return;

    QHBoxLayout* busyLayout = l->findChild<QHBoxLayout*>(kBusyLayoutObjectName);
    Q_ASSERT(busyLayout);
    if (!busyLayout)
        return;

    QObjectList::const_iterator it = busyLayout->children().begin();
    while(*it++)
        delete *it;

    delete busyLayout;
}

void EmailAccountWizardAccountPage::enumerationFinished()
{
    Q_D(EmailAccountWizardAccountPage);

    ForgettableWatcherType* watcher = dynamic_cast<ForgettableWatcherType*>(
        sender());
    Q_ASSERT(watcher);
    if (!watcher)
        return;

    QList<ServiceProviderInfo*>* result = watcher->result();
    if (!d->m_futureStarted || d->m_futureWatcher != watcher) {
        // Delete QFuture results from the forgotten watchers
        if (result) {
            qDeleteAll(*result);
            delete result;
        }

        return;
    }

    // Get the result
    EmailAccountWizard* w = dynamic_cast<EmailAccountWizard*>(wizard());
    Q_ASSERT(w);
    if (w)
        w->adoptResult(result);

    stopBusyIndicator();
    enableButtons();
    next();
}

QList<ServiceProviderInfo*>*
EmailAccountWizardAccountPage::enumerateServiceProviders(
    const QString& domainName) const
{
    QScopedPointer<AccountEnumerator> enumerator(
        AccountManagerFactory::createMozillaAccountEnumerator(domainName));
    Q_ASSERT(enumerator);
    if (!enumerator)
        return 0;

    return enumerator->enumerateAccounts();
}

EmailAccountWizardIncomingServerPage::EmailAccountWizardIncomingServerPage(
    QWidget* parent) : QWizardPage(parent)
{
    setTitle(tr("Incoming server details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* usernameLabel = new QLabel(tr("Account username:"));
    Widgets::CustomEditLine* usernameEditLine = new Widgets::CustomEditLine();
    usernameEditLine->setEmptyMessage(tr("Username"));
    registerField(kFieldIncomingServerUsername, usernameEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    Widgets::CustomEditLine* passwordEditLine = new Widgets::CustomEditLine();
    passwordEditLine->setEmptyMessage(tr("Password"));
    passwordEditLine->setEchoMode(QLineEdit::Password);
    registerField(kFieldIncomingServerPassword, passwordEditLine);

    QStringList incomingTypes;
    incomingTypes << "POP3" << "IMAP" << "Maildir";

    QLabel* incomingTypeLabel = new QLabel(tr("Incoming server type:"));
    QComboBox* incomingTypeComboBox = new QComboBox();
    incomingTypeComboBox->insertItems(0, incomingTypes);
    registerField(kFieldIncomingServerType, incomingTypeComboBox);

    QLabel* incomingHostnameLabel = new QLabel(tr("Hostname:"));
    Widgets::CustomEditLine* incomingHostnameEditLine =
        new Widgets::CustomEditLine();
    incomingHostnameEditLine->setEmptyMessage(tr("Server hostname"));
    registerField(kFieldIncomingServerHostname, incomingHostnameEditLine);

    QLabel* incomingPortLabel = new QLabel(tr("Port:"));
    Widgets::CustomEditLine* incomingPortEditLine =
        new Widgets::CustomEditLine();
    incomingPortEditLine->setEmptyMessage(tr("Server port"));
    registerField(kFieldIncomingServerPort, incomingPortEditLine);

    QStringList incomingSSL;
    incomingSSL << tr("Autodetect") << tr("None") << "STARTTLS" << "SSL/TLS";

    QLabel* incomingSSLLabel = new QLabel(tr("SSL:"));
    QComboBox* incomingSSLComboBox = new QComboBox();
    incomingSSLComboBox->insertItems(0, incomingSSL);
    registerField(kFieldIncomingServerSSL, incomingSSLComboBox);

    QStringList incomingAuth;
    incomingAuth << tr("Autodetect") << tr("Normal password")
        << tr("Encrypted password") << "Kerberos / GSSAPI" << "NTLM";

    QLabel* incomingAuthLabel = new QLabel(tr("Authentication:"));
    QComboBox* incomingAuthComboBox = new QComboBox();
    incomingAuthComboBox->insertItems(0, incomingAuth);
    registerField(kFieldIncomingServerAuth, incomingAuthComboBox);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameEditLine, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordEditLine, 1, 1);
    layout->addItem(new QSpacerItem(50, 20), 2, 0, 1, -1);
    layout->addWidget(incomingTypeLabel, 3, 0);
    layout->addWidget(incomingTypeComboBox, 3, 1);
    layout->addWidget(incomingHostnameLabel, 4, 0);
    layout->addWidget(incomingHostnameEditLine, 4, 1);
    layout->addWidget(incomingPortLabel, 5, 0);
    layout->addWidget(incomingPortEditLine, 5, 1);
    layout->addWidget(incomingSSLLabel, 6, 0);
    layout->addWidget(incomingSSLComboBox, 6, 1);
    layout->addWidget(incomingAuthLabel, 7, 0);
    layout->addWidget(incomingAuthComboBox, 7, 1);
    setLayout(layout);
}

EmailAccountWizardOutgoingServerPage::EmailAccountWizardOutgoingServerPage(
    QWidget* parent) : QWizardPage(parent)
{
    setTitle(tr("Outgoing server details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* usernameLabel = new QLabel(tr("Account username:"));
    Widgets::CustomEditLine* usernameEditLine = new Widgets::CustomEditLine();
    usernameEditLine->setEmptyMessage(tr("Username"));
    registerField(kFieldOutgoingServerUsername, usernameEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    Widgets::CustomEditLine* passwordEditLine = new Widgets::CustomEditLine();
    passwordEditLine->setEmptyMessage(tr("Password"));
    passwordEditLine->setEchoMode(QLineEdit::Password);
    registerField(kFieldOutgoingServerPassword, passwordEditLine);

    QStringList outgoingTypes;
    outgoingTypes << "SMTP" << "Sendmail";

    QLabel* outgoingTypeLabel = new QLabel(tr("Outgoing server type:"));
    QComboBox* outgoingTypeComboBox = new QComboBox();
    outgoingTypeComboBox->insertItems(0, outgoingTypes);
    registerField(kFieldOutgoingServerType, outgoingTypeComboBox);

    QLabel* outgoingHostnameLabel = new QLabel(tr("Hostname:"));
    Widgets::CustomEditLine* outgoingHostnameEditLine =
        new Widgets::CustomEditLine();
    outgoingHostnameEditLine->setEmptyMessage(tr("Server hostname"));
    registerField(kFieldOutgoingServerHostname, outgoingHostnameEditLine);

    QLabel* outgoingPortLabel = new QLabel(tr("Port:"));
    Widgets::CustomEditLine* outgoingPortEditLine =
        new Widgets::CustomEditLine();
    outgoingPortEditLine->setEmptyMessage(tr("Server port"));
    registerField(kFieldOutgoingServerPort, outgoingPortEditLine);

    QStringList outgoingSSL;
    outgoingSSL << tr("Autodetect") << tr("None") << "STARTTLS" << "SSL/TLS";

    QLabel* outgoingSSLLabel = new QLabel(tr("SSL:"));
    QComboBox* outgoingSSLComboBox = new QComboBox();
    outgoingSSLComboBox->insertItems(0, outgoingSSL);
    registerField(kFieldOutgoingServerSSL, outgoingSSLComboBox);

    QStringList outgoingAuth;
    outgoingAuth << tr("Autodetect") << tr("No authentication")
        << tr("Normal password") << tr("Encrypted password")
        << "Kerberos / GSSAPI" << "NTLM";

    QLabel* outgoingAuthLabel = new QLabel(tr("Authentication:"));
    QComboBox* outgoingAuthComboBox = new QComboBox();
    outgoingAuthComboBox->insertItems(0, outgoingAuth);
    registerField(kFieldOutgoingServerAuth, outgoingAuthComboBox);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameEditLine, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordEditLine, 1, 1);
    layout->addItem(new QSpacerItem(50, 20), 2, 0, 1, -1);
    layout->addWidget(outgoingTypeLabel, 3, 0);
    layout->addWidget(outgoingTypeComboBox, 3, 1);
    layout->addWidget(outgoingHostnameLabel, 4, 0);
    layout->addWidget(outgoingHostnameEditLine, 4, 1);
    layout->addWidget(outgoingPortLabel, 5, 0);
    layout->addWidget(outgoingPortEditLine, 5, 1);
    layout->addWidget(outgoingSSLLabel, 6, 0);
    layout->addWidget(outgoingSSLComboBox, 6, 1);
    layout->addWidget(outgoingAuthLabel, 7, 0);
    layout->addWidget(outgoingAuthComboBox, 7, 1);
    setLayout(layout);
}

EmailAccountWizardFinishedPage::EmailAccountWizardFinishedPage(QWidget* parent) :
    QWizardPage(parent)
{
    setTitle(tr("Finished"));

    QLabel* label = new QLabel(tr("You have succesfully setup your email "
        "account."));
    label->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
}

} // namespace Pages


class EmailAccountWizardPrivate
{
public:
    EmailAccountWizardPrivate(QList<ServiceProviderInfo*>* result = 0) :
        m_result(result)
    {
    }

    ~EmailAccountWizardPrivate()
    {
        if (m_result)
            qDeleteAll(*m_result);
    }

    void swap(EmailAccountWizardPrivate& wizardPrivate)
    {
        m_result.swap(wizardPrivate.m_result);
    }

    QScopedPointer<QList<ServiceProviderInfo*> > m_result;
};

EmailAccountWizard::EmailAccountWizard(QWidget *parent) :
QWizard(parent), d_ptr(new EmailAccountWizardPrivate())
{
    setWindowTitle(tr("Add new email account"));

    addPage(new Pages::EmailAccountWizardIntroPage());
    addPage(new Pages::EmailAccountWizardAccountPage());
    addPage(new Pages::EmailAccountWizardIncomingServerPage());
    addPage(new Pages::EmailAccountWizardOutgoingServerPage());
    addPage(new Pages::EmailAccountWizardFinishedPage());
}

EmailAccountWizard::~EmailAccountWizard()
{
}

QList<ServiceProviderInfo*>* EmailAccountWizard::getResult() const
{
    Q_D(const EmailAccountWizard);
    return d->m_result.data();
}

void EmailAccountWizard::adoptResult(QList<ServiceProviderInfo*>* result)
{
    Q_ASSERT(result);
    QScopedPointer<EmailAccountWizardPrivate> tmp(
        new EmailAccountWizardPrivate(result));
    d_ptr.swap(tmp);
}


} // namespace Wizards
} // namespace Maily
