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

#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractItemModel>

namespace maily {
namespace models {

namespace details {
class AccountModelPrivate;
} // namespace details

class AccountModel : public QAbstractItemModel {
	Q_OBJECT

public:
	AccountModel(QObject *parent = 0);
	virtual ~AccountModel();

	//
	// Getters and setters
	//

private:
	details::AccountModelPrivate *m_d;
};

} // namespace models
} // namespace maily

#endif // ACCOUNTMODEL_h
