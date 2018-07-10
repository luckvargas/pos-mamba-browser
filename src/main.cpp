/* Stone Payments Browser for Mamba application development
    Copyright (C) <2018>
    Author: Luciano Santos - lvsantos@stone.com.br

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include <QScreen>
#include <QtGui>

int
main(int argc, char* argv[])
{
  { // Environment variables to run on embedded linux
    qputenv("QWS_MOUSE_PROTO", "linuxinput:/dev/input/event2");
    qputenv("QWS_KEYBOARD", "linuxinput:/dev/input/event0");
    qputenv("QWS_DISPLAY", "Transformed:Rot270:LinuxFb:/dev/graphics/fb0");
  }

  QApplication app(argc, argv);
  app.setApplicationName("MambaWebBrowser");
  app.setOrganizationName("Stone Payments S.A.");
  app.setOrganizationDomain("stone.com.br");

  // Setup initialization url
  QUrl url;
  if (argc > 1) {
    url = QUrl(argv[1]);
  } else {
    url = QUrl("http://www.stone.com.br/");
  }

  MainWindow* browser = new MainWindow(url);
  //  QWebSettings::globalSettings()->setAttribute(
  //    QWebSettings::DeveloperExtrasEnabled, true);

  QRect rec = QApplication::desktop()->screenGeometry();
  if (rec.height() < browser->size().rheight()) {
    // embedded devices
    browser->showFullScreen();
  } else {
    // desktop
    browser->show();
  }

  ///< Application properties
  browser->setWindowIcon(QIcon(":/icon.png"));

  return app.exec();
}
