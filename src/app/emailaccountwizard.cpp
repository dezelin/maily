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

const int kPageIdIntro = 0;
const int kPageIdEmailAccount = 1;
const int kPageIdEmailIncommingServer = 2;
const int kPageIdEmailOutgoingServer = 3;
const int kPageIdFinished = 4;

const QString kBusyLayoutObjectName = "busyLayoutObject";

const QString kFieldFullName = "fullName*";
const QString kFieldEmailAddress = "emailAddress*";
const QString kFieldPassword = "password";
const QString kFieldSavePassword = "savePassword";
const QString kFieldIncommingServerUsername = "incommingServerUsername*";
const QString kFieldIncommingServerPassword = "incommingServerPassword*";
const QString kFieldIncommingServerType = "incommingServerType";
const QString kFieldIncommingServerHostname = "incommingServerHostname*";
const QString kFieldIncommingServerPort = "incommingServerPort";
const QString kFieldIncommingServerSSL = "incommingServerSSL";
const QString kFieldIncommingServerAuth = "incommingServerAuth";
const QString kFieldOutgoingServerUsername = "outgoingServerUsername*";
const QString kFieldOutgoingServerPassword = "outgoingServerPassword*";
const QString kFieldOutgoingServerType = "outgoingServerType";
const QString kFieldOutgoingServerHostname = "outgoingServerHostname*";
const QString kFieldOutgoingServerPort = "outgoingServerPort";
const QString kFieldOutgoingServerSSL = "outgoingServerSSL";
const QString kFieldOutgoingServerAuth = "outgoingServerAuth";


EmailAccountWizard::EmailAccountWizard(QWidget *parent) :
    QWizard(parent)
{
    setWindowTitle(tr("Add new email account"));

    addPage(new Pages::EmailAccountWizardIntroPage());
    addPage(new Pages::EmailAccountWizardAccountPage());
    addPage(new Pages::EmailAccountWizardIncommingServerPage());
    addPage(new Pages::EmailAccountWizardOutgoingServerPage());
    addPage(new Pages::EmailAccountWizardFinishedPage());
}


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

struct EmailAccountWizardAccountPage::EmailAccountWizardAccountPagePrivate
{
    EmailAccountWizardAccountPagePrivate() :
        m_futureStarted(false), m_futureWatcher(0)
    {
    }

    typedef EmailAccountWizardAccountPage::ServiceProviderInfoListPtr
        ServiceProviderInfoListPtr;

    bool m_futureStarted;
    Services::Tasks::ForgettableWatcher<ServiceProviderInfoListPtr>* m_futureWatcher;
};

EmailAccountWizardAccountPage::EmailAccountWizardAccountPage(QWidget* parent) :
    QWizardPage(parent),
    m_data(new EmailAccountWizardAccountPagePrivate())
{
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
    emailAddressEditLine->setValidator(
        new Widgets::Validators::EmailValidator());
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
    Q_ASSERT(m_data);
    if (!m_data)
        return;

    bool started = m_data->m_futureStarted;
    if (started) {
        //m_data->m_futureWatcher.waitForFinished();
        m_data->m_futureStarted = false;
        m_data->m_futureWatcher->disconnect(this);
        stopBusyIndicator();
    }
}

void EmailAccountWizardAccountPage::initializePage()
{
    Q_ASSERT(m_data);
    if (!m_data)
        return;

}

int EmailAccountWizardAccountPage::nextId() const
{
    Q_ASSERT(m_data);
    if (!m_data)
        return false;

    bool started = m_data->m_futureStarted;
    if (!started)
        return kPageIdEmailIncommingServer;

    m_data->m_futureStarted = false; // we will proceed to the next page

    Q_ASSERT(m_data->m_futureWatcher);
    if (!m_data->m_futureWatcher)
        return kPageIdEmailIncommingServer;

    //bool foundProvider = !m_data->m_futureWatcher.result()->isEmpty();
    bool foundProvider = !m_data->m_futureWatcher->result()->isEmpty();
    if (foundProvider)
        return kPageIdFinished;

    return kPageIdEmailIncommingServer;
}

bool EmailAccountWizardAccountPage::validatePage()
{
    Q_ASSERT(m_data);
    if (!m_data)
        return false;

    bool started = m_data->m_futureStarted;
    bool finished = (m_data->m_futureWatcher) ? m_data->m_futureWatcher->isFinished()
        : false;
    if (started && finished)
        return true;

    startBusyIndicator();
    disableButtons();

    QFuture<ServiceProviderInfoListPtr> future = QtConcurrent::run(
        this, &EmailAccountWizardAccountPage::enumerateServiceProviders,
            QString("gmail.com"));

    typedef QScopedPointer<Services::Tasks::ForgettableWatcher<ServiceProviderInfoListPtr> >
        ForgettableWatcherPtr;

    ForgettableWatcherPtr futureWatcher(
        new Services::Tasks::ForgettableWatcher<ServiceProviderInfoListPtr>());

//    connect(&m_data->m_futureWatcher, SIGNAL(finished()), this,
//        SLOT(enumerationFinished()));

    connect(futureWatcher.data(), SIGNAL(finished()), this, SLOT(enumerationFinished()));
    futureWatcher->setFuture(future);

    Q_ASSERT(m_data);
    m_data->m_futureWatcher = futureWatcher.take();
    m_data->m_futureStarted = true;

    // FutureWatcher will call enumerationFinished() when finished
    // so return here false and stop proceeding to the next page temporaly.
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
    stopBusyIndicator();
    enableButtons();
    next();
}

EmailAccountWizardAccountPage::ServiceProviderInfoListPtr
EmailAccountWizardAccountPage::enumerateServiceProviders(
    const QString& domainName) const
{
    QScopedPointer<Services::AccountEnumerator> enumerator(
        Services::AccountManagerFactory::createMozillaAccountEnumerator(
            domainName));
    Q_ASSERT(enumerator);
    if (!enumerator)
        return ServiceProviderInfoListPtr();

    ServiceProviderInfoListPtr providers(new ServiceProviderInfoList());
    ServiceProviderInfoPtr info(new Services::ServiceProviderInfo());
    providers->append(info);

    QMutex dummy;
    dummy.lock();
    QWaitCondition waitCondition;
    waitCondition.wait(&dummy, 20000);

    return providers;
}

EmailAccountWizardIncommingServerPage::EmailAccountWizardIncommingServerPage(
    QWidget* parent) : QWizardPage(parent)
{
    setTitle(tr("Incomming server details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* usernameLabel = new QLabel(tr("Account username:"));
    Widgets::CustomEditLine* usernameEditLine = new Widgets::CustomEditLine();
    usernameEditLine->setEmptyMessage(tr("Username"));
    registerField(kFieldIncommingServerUsername, usernameEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    Widgets::CustomEditLine* passwordEditLine = new Widgets::CustomEditLine();
    passwordEditLine->setEmptyMessage(tr("Password"));
    passwordEditLine->setEchoMode(QLineEdit::Password);
    registerField(kFieldIncommingServerPassword, passwordEditLine);

    QStringList incommingTypes;
    incommingTypes << "POP3" << "IMAP" << "Maildir";

    QLabel* incommingTypeLabel = new QLabel(tr("Incomming server type:"));
    QComboBox* incommingTypeComboBox = new QComboBox();
    incommingTypeComboBox->insertItems(0, incommingTypes);
    registerField(kFieldIncommingServerType, incommingTypeComboBox);

    QLabel* incommingHostnameLabel = new QLabel(tr("Hostname:"));
    Widgets::CustomEditLine* incommingHostnameEditLine =
        new Widgets::CustomEditLine();
    incommingHostnameEditLine->setEmptyMessage(tr("Server hostname"));
    registerField(kFieldIncommingServerHostname, incommingHostnameEditLine);

    QLabel* incommingPortLabel = new QLabel(tr("Port:"));
    Widgets::CustomEditLine* incommingPortEditLine =
        new Widgets::CustomEditLine();
    incommingPortEditLine->setEmptyMessage(tr("Server port"));
    registerField(kFieldIncommingServerPort, incommingPortEditLine);

    QStringList incommingSSL;
    incommingSSL << tr("Autodetect") << tr("None") << "STARTTLS" << "SSL/TLS";

    QLabel* incommingSSLLabel = new QLabel(tr("SSL:"));
    QComboBox* incommingSSLComboBox = new QComboBox();
    incommingSSLComboBox->insertItems(0, incommingSSL);
    registerField(kFieldIncommingServerSSL, incommingSSLComboBox);

    QStringList incommingAuth;
    incommingAuth << tr("Autodetect") << tr("Normal password")
        << tr("Encrypted password") << "Kerberos / GSSAPI" << "NTLM";

    QLabel* incommingAuthLabel = new QLabel(tr("Authentication:"));
    QComboBox* incommingAuthComboBox = new QComboBox();
    incommingAuthComboBox->insertItems(0, incommingAuth);
    registerField(kFieldIncommingServerAuth, incommingAuthComboBox);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameEditLine, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordEditLine, 1, 1);
    layout->addItem(new QSpacerItem(50, 20), 2, 0, 1, -1);
    layout->addWidget(incommingTypeLabel, 3, 0);
    layout->addWidget(incommingTypeComboBox, 3, 1);
    layout->addWidget(incommingHostnameLabel, 4, 0);
    layout->addWidget(incommingHostnameEditLine, 4, 1);
    layout->addWidget(incommingPortLabel, 5, 0);
    layout->addWidget(incommingPortEditLine, 5, 1);
    layout->addWidget(incommingSSLLabel, 6, 0);
    layout->addWidget(incommingSSLComboBox, 6, 1);
    layout->addWidget(incommingAuthLabel, 7, 0);
    layout->addWidget(incommingAuthComboBox, 7, 1);
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

} // namespace wizards
} // namespace maily
