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

#include <QMainWindow>
#include <QObject>

class QLineEdit;
class QPushButton;
class QUrl;
class QHBoxLayout;
class QWebInspector;
class QLineEdit;
class QLabel;

class WebView;

const QSize defaultSize = QSize(240, 300);

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(const QUrl& url);

private slots:
  void setProgress(int p);
  void finishLoading(bool);
  void adjustTitle();
  void changeLocation();
  void adjustLocation();

  void on_actionOpen_triggered();
  void on_actionDebug_triggered();

private:
  void setupUi();

  QPushButton* m_buttonDebug;
  QPushButton* m_buttonOpenFile;
  QLabel* m_posFrame;
  QLineEdit* m_addressBar;
  WebView* m_webview;
  QWebInspector* m_webinspector;
  QHBoxLayout* m_layout;

  int m_loadProgress;
};
