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
#include <QLineEdit>
#include <QToolBar>
#include <QtWebKit>

MainWindow::MainWindow(const QUrl& url)
{

  m_webview = new QWebView(this);

  setupUi();
  connect(m_webview, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
  connect(m_webview, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
  connect(m_webview, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

  m_webview->load(url);
}

void
MainWindow::setupUi()
{
  m_addressBar = new QLineEdit(this);
  m_addressBar->setSizePolicy(QSizePolicy::Expanding,
                              m_addressBar->sizePolicy().verticalPolicy());
  connect(m_addressBar, SIGNAL(returnPressed()), SLOT(changeLocation()));

  QToolBar* toolBar = addToolBar(tr("Navigation"));
  toolBar->addAction(m_webview->pageAction(QWebPage::Back));
  toolBar->addAction(m_webview->pageAction(QWebPage::Forward));
  toolBar->addAction(m_webview->pageAction(QWebPage::Reload));
  toolBar->addAction(m_webview->pageAction(QWebPage::Stop));
  toolBar->addWidget(m_addressBar);

  setCentralWidget(m_webview);
}

void
MainWindow::changeLocation()
{
  QUrl url = QUrl(m_addressBar->text());
  m_webview->load(url);
  m_webview->setFocus();
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
