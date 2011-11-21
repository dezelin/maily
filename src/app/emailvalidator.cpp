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

#include <QUrl>

#include "emailvalidator.h"
#include "tools.h"

namespace Maily
{
namespace Widgets
{
namespace Validators
{

static const char email_rx[] = "[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'"
    "*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?";


EmailValidator::EmailValidator(QObject* parent) :
     QRegExpValidator(QRegExp(email_rx), parent)
{
}

void EmailValidator::fixup(QString& input) const
{
    Q_VOID(input)
}

QValidator::State EmailValidator::validate(QString& str, int& pos) const
{
    const int atIdx = str.lastIndexOf('@');
    if (atIdx < 0 || str.endsWith('@'))
        return QRegExpValidator::validate(str, pos);

    // toAce/fromAce doesn't like intermediate domain names,
    // so we fix them up with something innocuous to help it
    // along, and which we strip again afterwards
    QString domain = str.mid(atIdx + 1).toLower();
    const int dotIndex = domain.lastIndexOf('.');
    const bool needsOrgAdded = domain.endsWith('.');
    // during typing, the domain might end with '-', which is okay
    // yeah, foo.s also disrupts fromAce, during typing this is okay
    const bool needsDotOrgAdded = !needsOrgAdded &&
        (dotIndex < 0 || dotIndex == domain.size() - 2 || domain.endsWith('-'));
    if (needsOrgAdded)
        domain += "org";

    if (needsDotOrgAdded)
        domain += "tmp.org";

    const QByteArray domainEncoded = QUrl::toAce(domain);
    const QString domainRestored = QUrl::fromAce(domainEncoded);
    QString encoded = str.left(atIdx) + '@' + QString::fromLatin1(domainEncoded);
    if (needsDotOrgAdded) {
        Q_ASSERT(encoded.endsWith(QLatin1String("tmp.org")));
        encoded.chop(7);
    }

    if (needsOrgAdded) {
        Q_ASSERT(encoded.endsWith(QLatin1String(".org")));
        encoded.chop(3); // '.' was part of domain before
    }

    if (domain != domainRestored)
        return Invalid;

    int dummyPosition = 0;
    return QRegExpValidator::validate(encoded, dummyPosition);
}

} // namespace Validators
} // namespace Widgets
} // namespace Maily
