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

#ifndef EMAILACCOUNTSQLQUERYMODEL_H
#define EMAILACCOUNTSQLQUERYMODEL_H

#include <QSqlQueryModel>

namespace maily {
namespace models {


class EmailAccountSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit EmailAccountSqlQueryModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:

public slots:

};

} // namespace models
} // namespace maily

#endif // EMAILACCOUNTSQLQUERYMODEL_H
