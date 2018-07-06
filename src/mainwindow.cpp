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
#include <QFileDialog>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QToolBar>
#include <QtWebKit>

MainWindow::MainWindow(const QUrl& url)
{

  m_webview = new QWebView(this);

  connect(m_webview, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
  connect(m_webview, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
  connect(m_webview, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
  connect(m_webview, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));

  setupUi();
  m_webview->load(url);

  // Enable web inspector
  m_webview->page()->settings()->setAttribute(
    QWebSettings::DeveloperExtrasEnabled, true);
}

void
MainWindow::setupUi()
{
  ///< ToolBar
  m_addressBar = new QLineEdit(this);
  m_addressBar->setSizePolicy(QSizePolicy::Expanding,
                              m_addressBar->sizePolicy().verticalPolicy());
  connect(m_addressBar, SIGNAL(returnPressed()), SLOT(changeLocation()));

  QPushButton* m_buttonOpen = new QPushButton;
  m_buttonOpen->setIcon(QIcon(":/icons/open_black_24dp_1x.png"));
  connect(m_buttonOpen, SIGNAL(clicked()), SLOT(on_actionOpen_triggered()));

  QToolBar* toolBar = addToolBar(tr("Navigation"));
  toolBar->setMovable(false);
  toolBar->addWidget(m_buttonOpen);
  toolBar->addWidget(m_addressBar);

  setCentralWidget(m_webview);
  m_webview->setFixedSize(defaultSize);
  adjustSize();
  setFixedSize(this->size());
}

void
MainWindow::changeLocation()
{
  QUrl url = QUrl::fromUserInput(m_addressBar->text());
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
MainWindow::adjustLocation()
{
  m_addressBar->setText(m_webview->url().toString());
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

void
MainWindow::on_actionOpen_triggered()
{
  QString fileFullPath = QFileDialog::getOpenFileName(
    this, tr("Open File"), "", tr("HTML Files (*.html)"));

  if (fileFullPath.length() > 0) {
    m_webview->load(fileFullPath);
  }
}
