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

#include <QWizard>
#include <QWizardPage>

namespace maily
{
namespace wizards
{

class EmailAccountWizard : public QWizard
{
    Q_OBJECT
public:
    explicit EmailAccountWizard(QWidget *parent = 0);

signals:

public slots:

private slots:
  void onPageChanged(int id);

private:
  QWizardPage* createIntroPage();
  QWizardPage* createEmailAccountPage();
  QWizardPage* createEmailAccountManualPage();
  QWizardPage* createFinishedPage();
};

} // namespace wizards
} // namespace maily

#endif // EMAILACCOUNTWIZARD_H
