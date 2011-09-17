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
#include <QString>

namespace maily {
namespace models {

namespace details {
struct AccountModelPrivate;
} // namespace details

class AccountModel : public QAbstractItemModel {
	Q_OBJECT

public:
	AccountModel(QObject *parent = 0);
	virtual ~AccountModel();

	//
	// Getters and setters
	//

	const QString& name() const;
	void setName(const QString& name);

	const QString& filePath() const;
	void setFilePath(const QString& filePath);

	//
	// Overrides
	//

	virtual bool load(const QString& filePath) = 0;
	virtual bool save() = 0;

protected:
	//
	// Overrides
	//

	virtual bool createTables() = 0;

private:
	details::AccountModelPrivate *m_d;
};

} // namespace models
} // namespace maily

#endif // ACCOUNTMODEL_h
