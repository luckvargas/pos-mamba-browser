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
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QStatusBar>
#include <QToolBar>
#include <QtWebKit>

MainWindow::MainWindow(const QUrl& url)
{
  setupUi();

  connect(m_webview, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
  connect(m_webview, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
  connect(m_webview, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
  connect(m_webview, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));

  m_webview->load(url);
}

void
MainWindow::setupUi()
{
  ///< Webview and web inspector
  QPixmap image(":/images/S920.png");
  m_posFrame = new QLabel(this);
  m_posFrame->setPixmap(image);
  m_posFrame->setFixedSize(image.width(), image.height());

  m_webview = new QWebView(m_posFrame);
  m_webview->setStyleSheet("background-color: white");
  m_webview->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,
                                      true);
  m_webview->setFixedSize(defaultSize);
  m_webview->move(50, 252);

  m_webinspector = new QWebInspector(this);
  m_webinspector->setPage(m_webview->page());
  m_webinspector->setVisible(false);

  m_layout = new QHBoxLayout(this);
  m_layout->addWidget(m_posFrame);
  m_layout->addWidget(m_webinspector);

  QWidget* centralWidget = new QWidget(this);
  centralWidget->setLayout(m_layout);
  setCentralWidget(centralWidget);
  ///< ToolBar
  m_addressBar = new QLineEdit(this);
  m_addressBar->setSizePolicy(QSizePolicy::Expanding,
                              m_addressBar->sizePolicy().verticalPolicy());
  connect(m_addressBar, SIGNAL(returnPressed()), SLOT(changeLocation()));

  ///< Open html file button
  QPushButton* m_buttonOpen = new QPushButton;
  m_buttonOpen->setIcon(QIcon(":/icons/open_black_24dp_1x.png"));
  connect(m_buttonOpen, SIGNAL(clicked()), SLOT(on_actionOpen_triggered()));

  ///< Show web inspector button
  QPushButton* m_buttonDebug = new QPushButton;
  m_buttonDebug->setIcon(QIcon(":/icons/debug_black_24dp_1x.png"));
  connect(m_buttonDebug, SIGNAL(clicked()), SLOT(on_actionDebug_triggered()));

  ///< Configure toolbar
  QToolBar* toolBar = addToolBar(tr("Navigation"));
  toolBar->setMovable(false);
  toolBar->addWidget(m_buttonOpen);
  toolBar->addWidget(m_addressBar);
  toolBar->addWidget(m_buttonDebug);
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

void
MainWindow::on_actionDebug_triggered()
{
  m_webinspector->setVisible(!m_webinspector->isVisible());
  adjustSize();
}
