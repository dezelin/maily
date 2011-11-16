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


#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWizardPage>

#include "busyindicatorwidget.h"
#include "emailaccountwizard.h"

namespace Maily
{
namespace Wizards
{

const int kPageIdIntro = 0;
const int kPageIdEmailAccount = 1;
const int kPageIdFinished = 2;

EmailAccountWizard::EmailAccountWizard(QWidget *parent) :
    QWizard(parent)
{
  addPage(createIntroPage());
  addPage(createEmailAccountPage());
  //addPage(createEmailAccountManualPage());
  addPage(createFinishedPage());
  setWindowTitle(tr("Add new email account"));

  connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(onPageChanged(int)));
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

  QLabel* busyLabel = new QLabel(tr("Checking the online database..."));
  Widgets::BusyIndicatorWidget* busyIndicator =
      new Widgets::BusyIndicatorWidget();

  QHBoxLayout* busyLayout = new QHBoxLayout();
  busyLayout->addWidget(busyLabel, Qt::AlignCenter);
  busyLayout->addWidget(busyIndicator, Qt::AlignRight);
  layout->addLayout(busyLayout, 3, 0, 1, -1);

  busyIndicator->start();

  return false;
}

QWizardPage* EmailAccountWizard::createIntroPage()
{
  QWizardPage* page = new QWizardPage();
  page->setTitle(tr("Introduction"));

  QLabel* label = new QLabel(tr("This wizard will help you setup a new email "
                                "account"));
  label->setWordWrap(true);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}

QWizardPage* EmailAccountWizard::createEmailAccountPage()
{
  QWizardPage* page = new QWizardPage();
  page->setTitle(tr("Email account user details"));
  page->setSubTitle(tr("Please fill all fields."));

  QLabel* userNameLabel = new QLabel(tr("Your full name:"));
  QLineEdit* userNameLineEdit = new QLineEdit();

  QLabel* emailAddressLabel = new QLabel(tr("Email address:"));
  QLineEdit* emailAddressLineEdit = new QLineEdit();

  QLabel* passwordLabel = new QLabel(tr("Account password:"));
  QLineEdit* passwordLineEdit = new QLineEdit();
  passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

  QGridLayout* layout = new QGridLayout();
  layout->addWidget(userNameLabel, 0, 0);
  layout->addWidget(userNameLineEdit, 0, 1);
  layout->addWidget(emailAddressLabel, 1, 0);
  layout->addWidget(emailAddressLineEdit, 1, 1);
  layout->addWidget(passwordLabel, 2, 0);
  layout->addWidget(passwordLineEdit, 2, 1);
  page->setLayout(layout);

  return page;
}

QWizardPage* EmailAccountWizard::createEmailAccountManualPage()
{
  return 0;
}

QWizardPage* EmailAccountWizard::createFinishedPage()
{
  QWizardPage* page = new QWizardPage();
  page->setTitle(tr("Finished"));

  QLabel* label = new QLabel(tr("You have succesfully setup your email "
                                "account."));
  label->setWordWrap(true);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}

} // namespace wizards
} // namespace maily
