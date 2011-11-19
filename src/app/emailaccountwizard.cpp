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
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWizardPage>

#include "accountmanagerfactory.h"
#include "busyindicatorwidget.h"
#include "emailaccountwizard.h"
#include "mozillaaccountenumerator.h"

namespace Maily
{
namespace Wizards
{

const int kPageIdIntro = 0;
const int kPageIdEmailAccount = 1;
const int kPageIdFinished = 2;

namespace Details
{

    struct EmailAccountWizardPrivate
    {
        QFuture<QList<Services::ServiceProviderInfo>*> m_future;
        QFutureWatcher<QList<Services::ServiceProviderInfo>*> m_futureWatcher;
    };

} // namespace Details


EmailAccountWizard::EmailAccountWizard(QWidget *parent) :
    QWizard(parent), m_data(new Details::EmailAccountWizardPrivate())
{
    setWindowTitle(tr("Add new email account"));

    addPage(new Pages::EmailAccountWizardIntroPage());
    addPage(new Pages::EmailAccountWizardAccountPage());
    //addPage(createEmailAccountManualPage());
    addPage(new Pages::EmailAccountWizardFinishedPage());

    connect(&m_data->m_futureWatcher, SIGNAL(finished()), this,
        SLOT(enumerationFinished()));
}

EmailAccountWizard::~EmailAccountWizard()
{
    delete m_data;
}

bool EmailAccountWizard::validateCurrentPage()
{
    if (currentId() != kPageIdEmailAccount)
        return true;

    QWizardPage* page = currentPage();
    Q_ASSERT(page);
    if (!page)
        return false;

    QGridLayout* layout = dynamic_cast<QGridLayout*>(page->layout());
    Q_ASSERT(layout);
    if (!layout)
        return false;

    QLabel* busyLabel = new QLabel(tr("<b>Checking the online database...</b>"));
    Widgets::BusyIndicatorWidget* busyIndicator =
            new Widgets::BusyIndicatorWidget();

    QHBoxLayout* busyLayout = new QHBoxLayout();
    busyLayout->addWidget(busyLabel, Qt::AlignCenter);
    busyLayout->addWidget(busyIndicator, Qt::AlignRight);
    layout->addLayout(busyLayout, layout->rowCount() + 1, 0, 1, -1);

    busyIndicator->start();
    disableButtons();

    Q_ASSERT(m_data);
    m_data->m_future = QtConcurrent::run(this,
        &EmailAccountWizard::enumerateServiceProviders, QString("gmail.com"));
    m_data->m_futureWatcher.setFuture(m_data->m_future);

    return false;
}

void EmailAccountWizard::disableButtons()
{
    QAbstractButton* backButton = button(QWizard::BackButton);
    QAbstractButton* nextButton = button(QWizard::NextButton);
    QAbstractButton* cancelButton = button(QWizard::CancelButton);
    Q_ASSERT(backButton && nextButton && cancelButton);
    if (!backButton || !nextButton || !cancelButton)
        return;

    backButton->setEnabled(false);
    nextButton->setEnabled(false);
    cancelButton->setEnabled(false);
}

void EmailAccountWizard::enableButtons()
{
    QAbstractButton* backButton = button(QWizard::BackButton);
    QAbstractButton* nextButton = button(QWizard::NextButton);
    QAbstractButton* cancelButton = button(QWizard::CancelButton);
    Q_ASSERT(backButton && nextButton && cancelButton);
    if (!backButton || !nextButton || !cancelButton)
        return;

    backButton->setEnabled(true);
    nextButton->setEnabled(true);
    cancelButton->setEnabled(true);
}

void EmailAccountWizard::enumerationFinished()
{
    enableButtons();
    next();
}

QList<Services::ServiceProviderInfo>*
EmailAccountWizard::enumerateServiceProviders(const QString& domainName) const
{
    Services::AccountEnumerator* enumerator =
        Services::AccountManagerFactory::createMozillaAccountEnumerator(domainName);
    Q_ASSERT(enumerator);

    return 0;
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

EmailAccountWizardAccountPage::EmailAccountWizardAccountPage(QWidget* parent) :
    QWizardPage(parent)
{
    setTitle(tr("Email account user details"));
    setSubTitle(tr("Please fill all fields."));

    QLabel* userFullNameLabel = new QLabel(tr("Your full name:"));
    QLineEdit* userFullNameLineEdit = new QLineEdit();
    registerField("fullName*", userFullNameLineEdit);

    QLabel* emailAddressLabel = new QLabel(tr("Email address:"));
    QLineEdit* emailAddressLineEdit = new QLineEdit();
    registerField("emailAddress*", emailAddressLineEdit);

    QLabel* passwordLabel = new QLabel(tr("Account password:"));
    QLineEdit* passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    registerField("password", passwordLineEdit);

    QCheckBox* skipCheck = new QCheckBox(tr("Manually enter server information"));
    registerField("manualServerInfo", skipCheck);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(userFullNameLabel, 0, 0);
    layout->addWidget(userFullNameLineEdit, 0, 1);
    layout->addWidget(emailAddressLabel, 1, 0);
    layout->addWidget(emailAddressLineEdit, 1, 1);
    layout->addWidget(passwordLabel, 2, 0);
    layout->addWidget(passwordLineEdit, 2, 1);
    layout->addItem(new QSpacerItem(10, 30, QSizePolicy::Minimum,
                                    QSizePolicy::Fixed), 3, 0);
    layout->addWidget(skipCheck, 4, 0);
    setLayout(layout);
}

EmailAccountWizardFinishedPage::EmailAccountWizardFinishedPage(QWidget* parent) :
    QWizardPage(parent)
{
    setTitle(tr("Finished"));

    QLabel* label = new QLabel(tr("You have succesfully setup your email account."));
    label->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
}

} // namespace Pages

} // namespace wizards
} // namespace maily
