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

#include <QMainWindow>
#include <QObject>

class QUrl;
class QWebView;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(const QUrl& url);

protected slots:
  void setProgress(int p);
  void finishLoading(bool);
  void adjustTitle();

private:
  QWebView* m_webview;
  int m_loadProgress = 0;
};
