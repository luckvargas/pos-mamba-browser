/* Stone Pagamentos S.A Browser for Mamba application development
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
#include <QtGui>

int
main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  QUrl url;

  if (argc > 1) {
    url = QUrl(argv[1]);
  } else {
    url = QUrl("http://www.google.com/");
  }

  MainWindow* browser = new MainWindow(url);
  browser->show();

  return app.exec();
}
