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
#include <QLayout>
#include <QtWebKit>

MainWindow::MainWindow(const QUrl& url)
{

  m_webview = new QWebView(this);

  connect(m_webview, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
  connect(m_webview, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
  connect(m_webview, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

  setCentralWidget(m_webview);
  m_webview->load(url);
}

void
MainWindow::adjustTitle()
{
  if (m_loadProgress <= 0 || m_loadProgress >= 100) {
    setWindowTitle(m_webview->title());
  } else {
    setWindowTitle(
      QString("%1 (%2%)").arg(m_webview->title()).arg(m_loadProgress));
  }
}

void
MainWindow::setProgress(int p)
{
  m_loadProgress = p;
  adjustTitle();
}

void
MainWindow::finishLoading(bool)
{
  m_loadProgress = 100;
  adjustTitle();
}
