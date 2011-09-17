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

#include "emailaccountmodel.h"

namespace maily {
namespace models {

namespace details {

struct EmailAccountModelPrivate {

    EmailAccountModelPrivate() : serverType(POP3), sasl(false),
        saslFallback(false), username(""), password(""), tls(false),
        tlsRequired(false), address(""), port(0), rootPath(""), apop(false),
        apopFallback(false), needAuthentication(false), sendmailBinPath("") {
    }

    ServerType serverType;
    bool sasl;
    bool saslFallback;
    QString username;
    QString password;
    bool tls;
    bool tlsRequired;
    QString address;
    int port;
    QString rootPath;
    bool apop;
    bool apopFallback;
    bool needAuthentication;
    QString sendmailBinPath;
};

} // namespace details


EmailAccountModel::EmailAccountModel(QObject *parent) : AccountModel(parent),
    m_d(new details::EmailAccountModelPrivate()) {
}

EmailAccountModel::~EmailAccountModel() {
    delete m_d;
}

EmailAccountModel::ServerType EmailAccountModel::serverType() const {
    return m_d->serverType;
}

void EmailAccountModel::setServerType(ServerType serverType) {
    m_d->serverType = serverType;
}

bool EmailAccountModel::sasl() const {
    return m_d->sasl;
}

void EmailAccountModel::setSasl(bool sasl) {
    m_d->sasl = sasl;
}

bool EmailAccountModel::saslFallback() const {
    return m_d->saslFallback;
}

void EmailAccountModel::setSaslFallback(bool saslFallback) {
    m_d->saslFallback = saslFallback;
}

const QString& EmailAccountModel::username() const {
    return m_d->username;
}

void EmailAccountModel::setUsername(const QString& username) {
    m_d->username = username;
}

const QString& EmailAccountModel::password() const {
    return m_d->password;
}

void EmailAccountModel::setPassword(const QString& password) {
    m_d->password = password;
}

bool EmailAccountModel::tls() const {
    return m_d->tls;
}

void EmailAccountModel::setTls(bool tls) {
    m_d->tls = tls;
}

bool EmailAccountModel::tlsRequired() const {
    return m_d->tlsRequired;
}

void EmailAccountModel::setTlsRequired(bool tlsRequired) {
    m_d->tlsRequired = tlsRequired;
}

const QString& EmailAccountModel::address() const {
    return m_d->address;
}

void EmailAccountModel::setAddress(const QString& address) {
    m_d->address = address;
}

int EmailAccountModel::port() const {
    return m_d->port;
}

void EmailAccountModel::setPort(int port) {
    m_d->port = port;
}

const QString& EmailAccountModel::rootPath() const {
    return m_d->rootPath;
}

void EmailAccountModel::setRootPath(const QString& rootPath) {
    m_d->rootPath = rootPath;
}

bool EmailAccountModel::apop() const {
    return m_d->apop;
}

void EmailAccountModel::setApop(bool apop) {
    m_d->apop = apop;
}

bool EmailAccountModel::apopFallback() const {
    return m_d->apopFallback;
}

void EmailAccountModel::setApopFallback(bool apopFallback) {
    m_d->apopFallback = apopFallback;
}

bool EmailAccountModel::needAuthentication() const {
    return m_d->needAuthentication;
}

void EmailAccountModel::setNeedAuthentication(bool needAuthentication) {
    m_d->needAuthentication = needAuthentication;
}

const QString& EmailAccountModel::sendmailBinPath() const {
    return m_d->sendmailBinPath;
}

void EmailAccountModel::setSendmailBinPath(const QString& filePath) {
    m_d->sendmailBinPath = filePath;
}

bool EmailAccountModel::load(const QString &filePath) {

}

bool EmailAccountModel::save() {

}

bool EmailAccountModel::createTables() {

}


} // namespace models
} // namespace maily
