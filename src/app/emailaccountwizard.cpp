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
#include "emailserviceprovider.h"
#include "emailserviceproviderinfo.h"
#include "emailvalidator.h"
#include "mozillaaccountenumerator.h"
#include "serviceproviderfactory.h"
#include "tools.h"

namespace Maily
{
namespace Wizards
{

using namespace Maily::Services;
using namespace Maily::Services::Tasks;
using namespace Maily::Widgets;
using namespace Maily::Widgets::Validators;

const QString kBusyLayoutObjectName = "busyLayoutObject";

const QString kFieldFullName = "fullName";
const QString kFieldEmailAddress = "emailAddress";
const QString kFieldPassword = "password";
const QString kFieldSavePassword = "savePassword";
const QString kFieldIncomingServerUsername = "incommingServerUsername";
const QString kFieldIncomingServerPassword = "incommingServerPassword";
const QString kFieldIncomingServerType = "incommingServerType";
const QString kFieldIncomingServerHostname = "incommingServerHostname";
const QString kFieldIncomingServerPort = "incommingServerPort";
const QString kFieldIncomingServerSSL = "incommingServerSSL";
const QString kFieldIncomingServerAuth = "incommingServerAuth";
const QString kFieldOutgoingServerUsername = "outgoingServerUsername";
const QString kFieldOutgoingServerPassword = "outgoingServerPassword";
const QString kFieldOutgoingServerType = "outgoingServerType";
const QString kFieldOutgoingServerHostname = "outgoingServerHostname";
const QString kFieldOutgoingServerPort = "outgoingServerPort";
const QString kFieldOutgoingServerSSL = "outgoingServerSSL";
const QString kFieldOutgoingServerAuth = "outgoingServerAuth";

const int kPortPop3 = 110;
const int kPortPop3s = 995;
const int kPortImap = 143;
const int kPortImaps = 585;
const int kPortSmtp = 25;
const int kPortSmtps = 465;


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
    CustomEditLine* userFullNameEditLine = new CustomEditLine();
    userFullNameEditLine->setEmptyMessage(tr("Full name"));
    registerField(kFieldFullName + "*", userFullNameEditLine);

    QLabel* emailAddressLabel = new QLabel(tr("Email address:"));
    CustomEditLine* emailAddressEditLine = new CustomEditLine();
    emailAddressEditLine->setEmptyMessage(tr("Email address"));
    emailAddressEditLine->setValidator(d->m_emailValidator.data());
    registerField(kFieldEmailAddress + "*", emailAddressEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    CustomEditLine* passwordEditLine = new CustomEditLine();
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
        return EmailAccountWizard::PageEmailIncomingServer;

    d->m_futureStarted = false; // we will proceed to the next page

    Q_ASSERT(d->m_futureWatcher);
    if (!d->m_futureWatcher)
        return EmailAccountWizard::PageEmailIncomingServer;

    QList<ServiceProviderInfo*>* result = d->m_futureWatcher->result();
    bool foundProvider = (result) ? !d->m_futureWatcher->result()->isEmpty()
        : false;
    if (foundProvider) {
        d->m_futureWatcher = 0;
        return EmailAccountWizard::PageFinished;
    }

    return EmailAccountWizard::PageEmailIncomingServer;
}

bool EmailAccountWizardAccountPage::validatePage()
{
    Q_D(EmailAccountWizardAccountPage);

    bool started = d->m_futureStarted;
    bool finished = (d->m_futureWatcher) ? d->m_futureWatcher->isFinished()
        : false;
    if (started && finished)
        return true;

    startFutureWatcher();

    // FutureWatcher will call enumerationFinished() when finished
    // so return here false and stop proceeding to the next page temporarely.
    return false;
}

void EmailAccountWizardAccountPage::disableButtons()
{
    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
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
    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
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
    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
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
    BusyIndicatorWidget* busyIndicator = new BusyIndicatorWidget();

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

void EmailAccountWizardAccountPage::startFutureWatcher()
{
    Q_D(EmailAccountWizardAccountPage);

    QString emailAddress = field(kFieldEmailAddress).toString();
    Q_ASSERT(!emailAddress.isEmpty());
    if (emailAddress.isEmpty())
        return;

    int index = emailAddress.indexOf('@');
    Q_ASSERT(index > 0);
    if (index < 1)
        return;

    QString domain = emailAddress.mid(index + 1);
    Q_ASSERT(!domain.isEmpty());
    if (domain.isEmpty())
        return;

    startBusyIndicator();
    disableButtons();

    QFuture<QList<ServiceProviderInfo*>*> future = QtConcurrent::run(
        this, &EmailAccountWizardAccountPage::enumerateServiceProviders,
            QString(domain));

    ForgettableWatcherType* futureWatcher = new ForgettableWatcherType();
    connect(futureWatcher, SIGNAL(finished()), this, SLOT(enumerationFinished()));
    futureWatcher->setFuture(future);

    d->m_futureWatcher = futureWatcher;
    d->m_futureStarted = true;
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
    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
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

class EmailAccountWizardIncomingServerPagePrivate
{
public:
    EmailAccountWizardIncomingServerPagePrivate() :
        changedDuringTest(false), usernameEditLine(0), passwordEditLine(0),
        typeComboBox(0), hostnameEditLine(0), sslComboBox(0), portEditLine(0),
        authComboBox(0)
    {
    }

    bool changedDuringTest;
    CustomEditLine* usernameEditLine;
    CustomEditLine* passwordEditLine;
    QComboBox* typeComboBox;
    CustomEditLine* hostnameEditLine;
    QComboBox* sslComboBox;
    CustomEditLine* portEditLine;
    QComboBox* authComboBox;
};

EmailAccountWizardIncomingServerPage::EmailAccountWizardIncomingServerPage(
    QWidget* parent) : QWizardPage(parent),
    d_ptr(new EmailAccountWizardIncomingServerPagePrivate())
{
    Q_D(EmailAccountWizardIncomingServerPage);

    setTitle(tr("Incoming server details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* usernameLabel = new QLabel(tr("Account username:"));
    CustomEditLine* usernameEditLine = new CustomEditLine();
    usernameEditLine->setEmptyMessage(tr("Username"));
    registerField(kFieldIncomingServerUsername + "*", usernameEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    CustomEditLine* passwordEditLine = new CustomEditLine();
    passwordEditLine->setEmptyMessage(tr("Password"));
    passwordEditLine->setEchoMode(QLineEdit::Password);
    registerField(kFieldIncomingServerPassword + "*", passwordEditLine);

    QStringList incomingTypes;
    incomingTypes << "POP3" << "IMAP" << "Maildir";

    QLabel* typeLabel = new QLabel(tr("Incoming server type:"));
    QComboBox* typeComboBox = new QComboBox();
    typeComboBox->insertItems(0, incomingTypes);
    registerField(kFieldIncomingServerType, typeComboBox);

    QLabel* hostnameLabel = new QLabel(tr("Hostname:"));
    CustomEditLine* hostnameEditLine = new CustomEditLine();
    hostnameEditLine->setEmptyMessage(tr("Server hostname"));
    registerField(kFieldIncomingServerHostname + "*", hostnameEditLine);

    QLabel* portLabel = new QLabel(tr("Port:"));
    CustomEditLine* portEditLine = new CustomEditLine();
    portEditLine->setEmptyMessage(tr("Server port"));
    portEditLine->setDisabled(true);
    registerField(kFieldIncomingServerPort, portEditLine);

    QStringList incomingSSL;
    incomingSSL << tr("Autodetect") << tr("None") << "STARTTLS" << "SSL / TLS";

    QLabel* sslLabel = new QLabel(tr("SSL:"));
    QComboBox* sslComboBox = new QComboBox();
    sslComboBox->insertItems(0, incomingSSL);
    registerField(kFieldIncomingServerSSL, sslComboBox);

    QStringList incomingAuth;
    incomingAuth << tr("Autodetect") << tr("Normal password")
        << tr("Encrypted password") << "Kerberos / GSSAPI" << "NTLM";

    QLabel* authLabel = new QLabel(tr("Authentication:"));
    QComboBox* authComboBox = new QComboBox();
    authComboBox->insertItems(0, incomingAuth);
    registerField(kFieldIncomingServerAuth, authComboBox);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameEditLine, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordEditLine, 1, 1);
    layout->addItem(new QSpacerItem(50, 20), 2, 0, 1, -1);
    layout->addWidget(typeLabel, 3, 0);
    layout->addWidget(typeComboBox, 3, 1);
    layout->addWidget(hostnameLabel, 4, 0);
    layout->addWidget(hostnameEditLine, 4, 1);
    layout->addWidget(portLabel, 5, 0);
    layout->addWidget(portEditLine, 5, 1);
    layout->addWidget(sslLabel, 6, 0);
    layout->addWidget(sslComboBox, 6, 1);
    layout->addWidget(authLabel, 7, 0);
    layout->addWidget(authComboBox, 7, 1);
    setLayout(layout);

    d->authComboBox = authComboBox;
    d->hostnameEditLine = hostnameEditLine;
    d->portEditLine = portEditLine;
    d->sslComboBox = sslComboBox;
    d->typeComboBox = typeComboBox;
    d->passwordEditLine = passwordEditLine;
    d->usernameEditLine = usernameEditLine;

    connect(usernameEditLine, SIGNAL(textChanged(QString)), this, SLOT(changed()));
    connect(passwordEditLine, SIGNAL(textChanged(QString)), this, SLOT(changed()));
    connect(typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));
    connect(sslComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));
    connect(authComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));
    connect(hostnameEditLine, SIGNAL(textChanged(QString)), this, SLOT(changed()));
    connect(portEditLine, SIGNAL(textChanged(QString)), this, SLOT(changed()));

    connect(this, SIGNAL(completeChanged()), this, SLOT(completeChanged()));

    connect(typeComboBox, SIGNAL(currentIndexChanged(int)), this,
        SLOT(incomingServerTypeIndexChanged(int)));

    connect(sslComboBox, SIGNAL(currentIndexChanged(int)), this,
        SLOT(incomingSSLIndexChanged(int)));
}

EmailAccountWizardIncomingServerPage::~EmailAccountWizardIncomingServerPage()
{
}

void EmailAccountWizardIncomingServerPage::initializePage()
{
    QWizardPage::initializePage();

    QString username = field(kFieldEmailAddress).toString();
    QString password = field(kFieldPassword).toString();

    int index = username.indexOf('@');
    if (index != -1)
        username = username.left(index);

    setField(kFieldIncomingServerUsername, username);
    setField(kFieldIncomingServerPassword, password);
}

void EmailAccountWizardIncomingServerPage::testButtonClicked(int which)
{
    Q_D(EmailAccountWizardIncomingServerPage);

    Q_ASSERT(which == QWizard::CustomButton1);
    if (which != QWizard::CustomButton1)
        return;

    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
    Q_ASSERT(w);
    if (!w)
        return;

    if (w->currentId() != EmailAccountWizard::PageEmailIncomingServer)
        return;

    QAbstractButton* testButton = w->button(QWizard::CustomButton1);
    Q_ASSERT(testButton);
    if (!testButton)
        return;

    updateTestButton(TestButtonRed);
    testButton->setText(tr("Testing..."));

    d->changedDuringTest = false;

    QFuture<bool> future = QtConcurrent::run(this,
        &EmailAccountWizardIncomingServerPage::test);
    ForgettableWatcher<bool>* futureWatcher = new ForgettableWatcher<bool>();
    connect(futureWatcher, SIGNAL(finished()), this, SLOT(testFinished()));
    futureWatcher->setFuture(future);
}

void EmailAccountWizardIncomingServerPage::changed()
{
    Q_D(EmailAccountWizardIncomingServerPage);

    d->changedDuringTest = true;
    completeChanged();
}

void EmailAccountWizardIncomingServerPage::completeChanged()
{
    updateTestButton(isComplete() ? TestButtonRed :TestButtonDisabled);
}

void EmailAccountWizardIncomingServerPage::incomingServerTypeIndexChanged(int index)
{
    Q_D(EmailAccountWizardIncomingServerPage);

    int ssl = d->sslComboBox->currentIndex();
    switch(index) {
        case 0: { // POP3
            if (ssl == 0)
                setField(kFieldIncomingServerPort, "");
            else {
                int port = (ssl == 1) ? kPortPop3 : kPortPop3s;
                setField(kFieldIncomingServerPort, port);
            }
            break;
        }
        case 1: { // IMAP
            if (ssl == 0)
                setField(kFieldIncomingServerPort, "");
            else {
                int port = (ssl == 1) ? kPortImap : kPortImaps;
                setField(kFieldIncomingServerPort, port);
            }
            break;
        }
        case 2: { // Maildir
            break;
        }
        default: {
            qFatalAssert(!"Unknown index.");
            break;
        }
    }

    d->authComboBox->setDisabled(index == 2);
    d->hostnameEditLine->setDisabled(index == 2);
    d->portEditLine->setDisabled(index == 2 || ssl == 0);
    d->sslComboBox->setDisabled(index == 2);
}

void EmailAccountWizardIncomingServerPage::incomingSSLIndexChanged(int index)
{
    Q_D(EmailAccountWizardIncomingServerPage);

    int type = d->typeComboBox->currentIndex();
    switch(type) {
        case 0: { // POP3
            if (index == 0)
                setField(kFieldIncomingServerPort, "");
            else {
                int port = (index == 1) ? kPortPop3 : kPortPop3s;
                setField(kFieldIncomingServerPort, port);
            }
            break;
        }
        case 1: { // IMAP
            if (index == 0)
                setField(kFieldIncomingServerPort, "");
            else {
                int port = (index == 1) ? kPortImap : kPortImaps;
                setField(kFieldIncomingServerPort, port);
            }
            break;
        }
        case 2: { // Maildir
            break;
        }
        default: {
            qFatalAssert(!"Unknown index.");
            break;
        }
    }

    d->portEditLine->setDisabled(index == 0);
}

void EmailAccountWizardIncomingServerPage::testFinished()
{
    Q_D(const EmailAccountWizardIncomingServerPage);

    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
    Q_ASSERT(w);
    if (!w)
        return;

    if (w->currentId() != EmailAccountWizard::PageEmailIncomingServer)
        return;

    ForgettableWatcher<bool>* futureWatcher =
        dynamic_cast<ForgettableWatcher<bool>*>(sender());
    Q_ASSERT(futureWatcher);
    if (!futureWatcher)
        return;

    bool result = futureWatcher->result();
    updateTestButton(!d->changedDuringTest && result ? TestButtonBlue : TestButtonRed);
}

bool EmailAccountWizardIncomingServerPage::test()
{
    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
    Q_ASSERT(w);
    if (!w)
        return false;

    QScopedPointer<EmailServiceProviderInfo> info(
        static_cast<EmailServiceProviderInfo*>(w->getResultFromIncomingPage()));
    Q_ASSERT(info);
    if (!info)
        return false;

    QScopedPointer<EmailServiceProvider> provider(
        ServiceProviderFactory::createProvider(*info));
    provider->setDummyCertVerifier(true);
    return provider->connect();
}

const QString kTestButtonStylesheetTemplate =
    "QPushButton {"
    "   color: white;"
    "   border: 1px solid %1;"
    "   border-radius: 1px;"
    "   background: %2;"
    "   width: %3;"
    "   height: %4;"
    "}"
    "QPushButton:hover {"
    "   border: 1px solid %5;"
    "   background: %6;"
    "}"
    "QPushButton:pressed {"
    "   background: %7;"
    "}";

const QString kDisabledTestButtonBorderColor = "#2d2d2d";
const QString kDisabledTestButtonBackgroundColor = "#2d2d2d";
const QString kDisabledTestButtonHoverBorderColor = "#2d2d2d";
const QString kDisabledTestButtonHoverBackgroundColor = "#2d2d2d";
const QString kDisabledTestButtonPressedBackgroundColor = "#2d2d2d";

const QString kRedTestButtonBorderColor = "#d94b38";
const QString kRedTestButtonBackgroundColor = "#d94b38";
const QString kRedTestButtonHoverBorderColor = "#7f2b20";
const QString kRedTestButtonHoverBackgroundColor = "#c54433";
const QString kRedTestButtonPressedBackgroundColor = "#d64937";

const QString kBlueTestButtonBorderColor = "#4a8bf4";
const QString kBlueTestButtonBackgroundColor = "#4a8bf4";
const QString kBlueTestButtonHoverBorderColor = "#305ba0";
const QString kBlueTestButtonHoverBackgroundColor = "#4480e0";
const QString kBlueTestButtonPressedBackgroundColor = "#4a8bf4";

void EmailAccountWizardIncomingServerPage::updateTestButton(TestButtonStyles style)
{
    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
    Q_ASSERT(w);
    if (!w)
        return;

    QAbstractButton* testButton = w->button(QWizard::CustomButton1);
    Q_ASSERT(testButton);
    if (!testButton)
        return;

    QAbstractButton* nextButton = w->button(QWizard::NextButton);
    Q_ASSERT(nextButton);
    if (!nextButton)
        return;

    int width = nextButton->geometry().width() - 2;
    int height = nextButton->geometry().height() - 2;

    QString styleSheet;
    switch (style) {
        case TestButtonDisabled: {
            QString backgroundColor = palette().background().color().name();
            styleSheet = kTestButtonStylesheetTemplate
                .arg(backgroundColor)
                .arg(backgroundColor)
                .arg(QString::number(width) + "px")
                .arg(QString::number(height) + "px")
                .arg(backgroundColor)
                .arg(backgroundColor)
                .arg(backgroundColor);
            testButton->setText("");
            testButton->setEnabled(false);
            break;
        }
        case TestButtonRed: {
            styleSheet = kTestButtonStylesheetTemplate
                .arg(kRedTestButtonBorderColor)
                .arg(kRedTestButtonBackgroundColor)
                .arg(QString::number(width) + "px")
                .arg(QString::number(height) + "px")
                .arg(kRedTestButtonHoverBorderColor)
                .arg(kRedTestButtonHoverBackgroundColor)
                .arg(kRedTestButtonPressedBackgroundColor);
            testButton->setText(tr("Test"));
            testButton->setEnabled(true);
            break;
        }
        case TestButtonBlue: {
            styleSheet = kTestButtonStylesheetTemplate
                .arg(kBlueTestButtonBorderColor)
                .arg(kBlueTestButtonBackgroundColor)
                .arg(QString::number(width) + "px")
                .arg(QString::number(height) + "px")
                .arg(kBlueTestButtonHoverBorderColor)
                .arg(kBlueTestButtonHoverBackgroundColor)
                .arg(kBlueTestButtonPressedBackgroundColor);
            testButton->setText(tr("Passed"));
            testButton->setEnabled(true);
            break;
        }
        default: {
            qFatalAssert(!"Unknown test button style.");
        }
    }

    testButton->setStyleSheet(styleSheet);
    testButton->setFocusPolicy(Qt::NoFocus);
}

class EmailAccountWizardOutgoingServerPagePrivate
{
public:
    EmailAccountWizardOutgoingServerPagePrivate() :
        usernameEditLine(0), passwordEditLine(0), typeComboBox(0),
        hostnameEditLine(0), sslComboBox(0), portEditLine(0), authComboBox(0)
    {
    }

    CustomEditLine* usernameEditLine;
    CustomEditLine* passwordEditLine;
    QComboBox* typeComboBox;
    CustomEditLine* hostnameEditLine;
    QComboBox* sslComboBox;
    CustomEditLine* portEditLine;
    QComboBox* authComboBox;
};

EmailAccountWizardOutgoingServerPage::EmailAccountWizardOutgoingServerPage(
    QWidget* parent) : QWizardPage(parent),
    d_ptr(new EmailAccountWizardOutgoingServerPagePrivate())
{
    Q_D(EmailAccountWizardOutgoingServerPage);

    setTitle(tr("Outgoing server details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* usernameLabel = new QLabel(tr("Account username:"));
    Widgets::CustomEditLine* usernameEditLine = new Widgets::CustomEditLine();
    usernameEditLine->setEmptyMessage(tr("Username"));
    registerField(kFieldOutgoingServerUsername + "*", usernameEditLine);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    Widgets::CustomEditLine* passwordEditLine = new Widgets::CustomEditLine();
    passwordEditLine->setEmptyMessage(tr("Password"));
    passwordEditLine->setEchoMode(QLineEdit::Password);
    registerField(kFieldOutgoingServerPassword + "*", passwordEditLine);

    QStringList outgoingTypes;
    outgoingTypes << "SMTP" << "Sendmail";

    QLabel* typeLabel = new QLabel(tr("Outgoing server type:"));
    QComboBox* typeComboBox = new QComboBox();
    typeComboBox->insertItems(0, outgoingTypes);
    registerField(kFieldOutgoingServerType, typeComboBox);

    QLabel* hostnameLabel = new QLabel(tr("Hostname:"));
    CustomEditLine* hostnameEditLine = new CustomEditLine();
    hostnameEditLine->setEmptyMessage(tr("Server hostname"));
    registerField(kFieldOutgoingServerHostname + "*", hostnameEditLine);

    QLabel* portLabel = new QLabel(tr("Port:"));
    CustomEditLine* portEditLine = new CustomEditLine();
    portEditLine->setEmptyMessage(tr("Server port"));
    portEditLine->setDisabled(true);
    registerField(kFieldOutgoingServerPort, portEditLine);

    QStringList outgoingSSL;
    outgoingSSL << tr("Autodetect") << tr("None") << "STARTTLS" << "SSL/TLS";

    QLabel* sslLabel = new QLabel(tr("SSL:"));
    QComboBox* sslComboBox = new QComboBox();
    sslComboBox->insertItems(0, outgoingSSL);
    registerField(kFieldOutgoingServerSSL, sslComboBox);

    QStringList outgoingAuth;
    outgoingAuth << tr("Autodetect") << tr("No authentication")
        << tr("Normal password") << tr("Encrypted password")
        << "Kerberos / GSSAPI" << "NTLM";

    QLabel* authLabel = new QLabel(tr("Authentication:"));
    QComboBox* authComboBox = new QComboBox();
    authComboBox->insertItems(0, outgoingAuth);
    registerField(kFieldOutgoingServerAuth, authComboBox);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameEditLine, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordEditLine, 1, 1);
    layout->addItem(new QSpacerItem(50, 20), 2, 0, 1, -1);
    layout->addWidget(typeLabel, 3, 0);
    layout->addWidget(typeComboBox, 3, 1);
    layout->addWidget(hostnameLabel, 4, 0);
    layout->addWidget(hostnameEditLine, 4, 1);
    layout->addWidget(portLabel, 5, 0);
    layout->addWidget(portEditLine, 5, 1);
    layout->addWidget(sslLabel, 6, 0);
    layout->addWidget(sslComboBox, 6, 1);
    layout->addWidget(authLabel, 7, 0);
    layout->addWidget(authComboBox, 7, 1);
    setLayout(layout);

    d->authComboBox = authComboBox;
    d->hostnameEditLine = hostnameEditLine;
    d->portEditLine = portEditLine;
    d->sslComboBox = sslComboBox;
    d->typeComboBox = typeComboBox;
    d->passwordEditLine = passwordEditLine;
    d->usernameEditLine = usernameEditLine;

    connect(typeComboBox, SIGNAL(currentIndexChanged(int)), this,
        SLOT(incomingServerTypeIndexChanged(int)));

    connect(sslComboBox, SIGNAL(currentIndexChanged(int)), this,
        SLOT(incomingSSLIndexChanged(int)));

    connect(authComboBox, SIGNAL(currentIndexChanged(int)), this,
        SLOT(incomingAuthIndexChanged(int)));
}

EmailAccountWizardOutgoingServerPage::~EmailAccountWizardOutgoingServerPage()
{
}

void EmailAccountWizardOutgoingServerPage::initializePage()
{
    QWizardPage::initializePage();

    QString username = field(kFieldIncomingServerUsername).toString();
    QString password = field(kFieldIncomingServerPassword).toString();
    QString hostname = field(kFieldIncomingServerHostname).toString();
    setField(kFieldOutgoingServerUsername, username);
    setField(kFieldOutgoingServerPassword, password);
    setField(kFieldOutgoingServerHostname, hostname);
}

void EmailAccountWizardOutgoingServerPage::incomingServerTypeIndexChanged(int index)
{
    Q_D(EmailAccountWizardOutgoingServerPage);

    int ssl = d->sslComboBox->currentIndex();
    switch(index) {
        case 0: { // SMTP
            if (ssl == 0)
                setField(kFieldOutgoingServerPort, "");
            else {
                int port = (ssl == 1) ? kPortSmtp : kPortSmtps;
                setField(kFieldOutgoingServerPort, port);
            }
            break;
        }
        case 1: { // Sendmail
            break;
        }
        default: {
            qFatalAssert(!"Unknown index.");
            break;
        }
    }

    d->authComboBox->setDisabled(index == 1);
    d->hostnameEditLine->setDisabled(index == 1);
    d->portEditLine->setDisabled(index == 1 || ssl == 0);
    d->sslComboBox->setDisabled(index == 1);
}

void EmailAccountWizardOutgoingServerPage::incomingSSLIndexChanged(int index)
{
    Q_D(EmailAccountWizardOutgoingServerPage);

    int type = d->typeComboBox->currentIndex();
    switch(type) {
        case 0: { // SMTP
            if (index == 0)
                setField(kFieldOutgoingServerPort, "");
            else {
                int port = (index == 1) ? kPortSmtp : kPortSmtps;
                setField(kFieldOutgoingServerPort, port);
            }
            break;
        }
        case 1: { // Sendmail
            break;
        }
        default: {
            qFatalAssert(!"Unknown index.");
            break;
        }
    }

    d->portEditLine->setDisabled(index == 0);
}

void EmailAccountWizardOutgoingServerPage::incomingAuthIndexChanged(int index)
{
    Q_D(EmailAccountWizardOutgoingServerPage);

    d->passwordEditLine->setDisabled(index == 1);
    d->usernameEditLine->setDisabled(index == 1);
}

void EmailAccountWizardOutgoingServerPage::testButtonClicked(int which)
{
    Q_ASSERT(which == QWizard::CustomButton1);
    if (which != QWizard::CustomButton1)
        return;

    EmailAccountWizard* w = static_cast<EmailAccountWizard*>(wizard());
    Q_ASSERT(w);
    if (!w)
        return;

    if (w->currentId() != EmailAccountWizard::PageEmailOutgoingServer)
        return;

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

    QScopedPointer<Pages::EmailAccountWizardIncomingServerPage> incomingPage(
        new Pages::EmailAccountWizardIncomingServerPage());
    QScopedPointer<Pages::EmailAccountWizardOutgoingServerPage> outgoingPage(
        new Pages::EmailAccountWizardOutgoingServerPage());

    connect(this, SIGNAL(customButtonClicked(int)), incomingPage.data(),
        SLOT(testButtonClicked(int)));
    connect(this, SIGNAL(customButtonClicked(int)), outgoingPage.data(),
        SLOT(testButtonClicked(int)));

    setPage(EmailAccountWizard::PageIntro,
        new Pages::EmailAccountWizardIntroPage());
    setPage(EmailAccountWizard::PageEmailAccount,
        new Pages::EmailAccountWizardAccountPage());
    setPage(EmailAccountWizard::PageEmailIncomingServer, incomingPage.take());
    setPage(EmailAccountWizard::PageEmailOutgoingServer, outgoingPage.take());
    setPage(EmailAccountWizard::PageFinished,
        new Pages::EmailAccountWizardFinishedPage());

    connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(currentIdChanged(int)));
}

EmailAccountWizard::~EmailAccountWizard()
{
}

QList<ServiceProviderInfo*>* EmailAccountWizard::getResult()
{
    Q_D(EmailAccountWizard);
    return d->m_result.take();
}

QList<ServiceProviderInfo*>* EmailAccountWizard::getResultFromFields()
{
    QScopedPointer<QList<ServiceProviderInfo*> > providers(
        new QList<ServiceProviderInfo*>());

    ServiceProviderInfo* incoming = getResultFromIncomingPage();
    if (incoming)
        providers->push_back(incoming);

    ServiceProviderInfo* outgoing = getResultFromOutgoingPage();
    if (outgoing)
        providers->push_back(outgoing);

    return providers.take();
}

ServiceProviderInfo* EmailAccountWizard::getResultFromIncomingPage()
{
    QScopedPointer<EmailServiceProviderInfo> info(
        new EmailServiceProviderInfo());

    QString username = field(kFieldIncomingServerUsername).toString();
    QString password = field(kFieldIncomingServerPassword).toString();
    int serverType = field(kFieldIncomingServerType).toInt();
    QString hostname = field(kFieldIncomingServerHostname).toString();
    int port = field(kFieldIncomingServerPort).toInt();
    int ssl = field(kFieldIncomingServerSSL).toInt();
    int auth = field(kFieldIncomingServerAuth).toInt();

    info->setUsername(username);
    info->setPassword(password);
    info->setAddress(hostname);
    info->setPort(port);
    info->setDisplayName(hostname);
    info->setDisplayShortName(hostname);

    switch(auth) {
        case 0: { // Autodetect
            info->setAuthenticationType(EmailServiceProviderInfo::AuthAuto);
            break;
        }
        case 1: { // Normal password
            info->setAuthenticationType(EmailServiceProviderInfo::AuthPlain);
            break;
        }
        case 2: { // Encrypted password
            info->setAuthenticationType(EmailServiceProviderInfo::AuthCleartext);
            break;
        }
        case 3: { // Kerberos / GSSAPI
            info->setAuthenticationType(EmailServiceProviderInfo::AuthKerberos);
            break;
        }
        case 4: { // NTLM
            info->setAuthenticationType(EmailServiceProviderInfo::AuthNTLM);
            break;
        }
        default: {
            qFatalAssert(!"Unknown authentication type.");
            break;
        }
    }

    switch(serverType) {
        case 0: { // POP3
            if (ssl > 1) { // STARTTLS or SSL/TLS
                info->setServiceType(EmailServiceProviderInfo::POP3S);
                info->setTls(true);
                info->setTlsRequired(false);
            } else if (ssl == 1) { // None
                info->setServiceType(EmailServiceProviderInfo::POP3);
                info->setTls(false);
                info->setTlsRequired(false);
            } else { // Autodetect
                info->setServiceType(EmailServiceProviderInfo::POP3S
                    | EmailServiceProviderInfo::POP3);
                info->setTls(true);
                info->setTlsRequired(false);
            }

            break;
        }
        case 1: { // IMAP
            if (ssl > 1) { // STARTTLS or SSL/TLS
                info->setServiceType(EmailServiceProviderInfo::IMAPS);
                info->setTls(true);
                info->setTlsRequired(false);
            } else if (ssl == 1) { // None
                info->setServiceType(EmailServiceProviderInfo::IMAP);
                info->setTls(false);
                info->setTlsRequired(false);
            } else { // Autodetect
                info->setServiceType(EmailServiceProviderInfo::IMAPS
                    | EmailServiceProviderInfo::IMAP);
                info->setTls(true);
                info->setTlsRequired(false);
            }

            break;
        }
        case 2: { // Maildir
            info->setServiceType(EmailServiceProviderInfo::MAILDIR);
        }
        default: {
            qFatalAssert(!"Unknown server type.")
            break;
        }
    }

    return info.take();
}

ServiceProviderInfo* EmailAccountWizard::getResultFromOutgoingPage()
{
    QScopedPointer<EmailServiceProviderInfo> info(
        new EmailServiceProviderInfo());

    QString username = field(kFieldOutgoingServerUsername).toString();
    QString password = field(kFieldOutgoingServerPassword).toString();
    int serverType = field(kFieldOutgoingServerType).toInt();
    QString hostname = field(kFieldOutgoingServerHostname).toString();
    int port = field(kFieldOutgoingServerPort).toInt();
    int ssl = field(kFieldOutgoingServerSSL).toInt();
    int auth = field(kFieldOutgoingServerAuth).toInt();

    info.reset(new EmailServiceProviderInfo());
    info->setUsername(username);
    info->setPassword(password);
    info->setAddress(hostname);
    info->setPort(port);
    info->setDisplayName(hostname);
    info->setDisplayShortName(hostname);

    switch(auth) {
        case 0: { // Autodetect
            info->setAuthenticationType(EmailServiceProviderInfo::AuthAuto);
            break;
        }
        case 1: { // No authentication
            info->setAuthenticationType(EmailServiceProviderInfo::AuthNone);
            break;
        }
        case 2: { // Normal password
            info->setAuthenticationType(EmailServiceProviderInfo::AuthPlain);
            break;
        }
        case 3: { // Encrypted password
            info->setAuthenticationType(EmailServiceProviderInfo::AuthCleartext);
            break;
        }
        case 4: { // Kerberos / GSSAPI
            info->setAuthenticationType(EmailServiceProviderInfo::AuthKerberos);
            break;
        }
        case 5: { // NTLM
            info->setAuthenticationType(EmailServiceProviderInfo::AuthNTLM);
            break;
        }
        default: {
            qFatalAssert(!"Unknown authentication type.");
            break;
        }
    }

    switch(serverType) {
        case 0: { // SMTP
            if (ssl > 1) { // STARTTLS or SSL/TLS
                info->setServiceType(EmailServiceProviderInfo::SMTPS);
                info->setTls(true);
                info->setTlsRequired(false);
            } else if (ssl == 1) { // None
                info->setServiceType(EmailServiceProviderInfo::SMTP);
                info->setTls(false);
                info->setTlsRequired(false);
            } else { // Autodetect
                info->setServiceType(EmailServiceProviderInfo::SMTPS
                    | EmailServiceProviderInfo::SMTP);
                info->setTls(true);
                info->setTlsRequired(false);
            }

            break;
        }
        case 2: { // Sendmail
            info->setServiceType(EmailServiceProviderInfo::SENDMAIL);
        }
        default: {
            qFatalAssert(!"Unknown server type.")
            break;
        }
    }

    return info.take();
}

void EmailAccountWizard::adoptResult(QList<ServiceProviderInfo*>* result)
{
    //Q_ASSERT(result);
    QScopedPointer<EmailAccountWizardPrivate> tmp(
        new EmailAccountWizardPrivate(result));
    d_ptr.swap(tmp);
}

void EmailAccountWizard::done(int result)
{
    if (result != QWizard::Accepted)
        QWizard::done(result);

    QList<ServiceProviderInfo*>* providers = getResult();
    if (!providers)
        providers = getResultFromFields();

    qDeleteAll(*providers);
    delete providers;

    QWizard::done(result);
}

void EmailAccountWizard::currentIdChanged(int id)
{
    if (id == -1)
        return;

    QList<QWizard::WizardButton> layout;
    Pages pageId = static_cast<Pages>(id);

    switch(pageId) {
        case PageIntro:
        case PageEmailAccount:
        case PageFinished: {
            setOption(HaveCustomButton1, false);
            layout << QWizard::Stretch << QWizard::BackButton
                << QWizard::NextButton << QWizard::FinishButton
                << QWizard::CancelButton;
            break;
        }
        case PageEmailIncomingServer:
        case PageEmailOutgoingServer: {
            setOption(HaveCustomButton1, true);
            setButtonText(CustomButton1, "");
            layout << QWizard::CustomButton1 << QWizard::Stretch
                << QWizard::BackButton << QWizard::NextButton
                << QWizard::FinishButton << QWizard::CancelButton;
            break;
        }
        default: {
            qFatalAssert(!"Unknown page id.");
            break;
        }
    }

    setButtonLayout(layout);
}

} // namespace Wizards
} // namespace Maily
