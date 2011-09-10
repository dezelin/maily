/* -*- mode: C++; c-file-style: "k&r" tab-width: 2; -*-
 *
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

#include "accountmodel.h"

namespace maily {
	namespace models {
		
		namespace details {
			class AccountModelPrivate {
			public:

			}
		} // namespace details

		AccountModel::AccountModel(QObject *parent) : QAbstractItemModel(parent),
			m_d(new details::AccountModelPrivate()) {
		}

		AccountModel::~AccountModel() {
			delete m_d;
		}

	} // namespace models
} // namespace maily

#endif // ACCOUNTMODEL_H
