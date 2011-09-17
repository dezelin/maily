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

#include "accountmodel.h"

namespace maily {
namespace models {

namespace details {

struct AccountModelPrivate {
    QString name;
    QString filePath;
};

} // namespace details

AccountModel::AccountModel(QObject *parent) : QAbstractItemModel(parent),
    m_d(new details::AccountModelPrivate()) {
}

AccountModel::~AccountModel() {
    delete m_d;
}

const QString& AccountModel::name() const {
    return m_d->name;
}

void AccountModel::setName(const QString &name) {
    m_d->name = name;
}

const QString& AccountModel::filePath() const {
    return m_d->filePath;
}

void AccountModel::setFilePath(const QString &filePath) {
    m_d->filePath = filePath;
}

} // namespace models
} // namespace maily
