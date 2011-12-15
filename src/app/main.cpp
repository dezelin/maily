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
 *   along with Maily.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "platform.h"

#include <QtGui/QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

#include <vmime/vmime.hpp>

#if defined(OS_WIN)
#include <vmime/platforms/windows/windowsHandler.hpp>
#else // OS_POSIX
#include <vmime/platforms/posix/posixHandler.hpp>
#endif

#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if defined(OS_WIN)
    vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();
#else // OS_POSIX
    vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
#endif

    QApplication app(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator mailyTranslator;
    mailyTranslator.load("maily" + QLocale::system().name());
    app.installTranslator(&mailyTranslator);

    MainWindow window;
    window.show();

    return app.exec();
}
