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

#include "webview.h"
#include "flickcharm.h"
#include <QApplication>
#include <QMouseEvent>

WebView::WebView(QWidget* parent)
  : QWebView(parent)
{
  FlickCharm* flickCharm = new FlickCharm(this);
  flickCharm->activateOn(this);

  setMouseTracking(true);
}

WebView::~WebView() {}

void
WebView::mouseMoveEvent(QMouseEvent* event)
{
  m_mousePos = event->pos();
  update();
}

void
WebView::paintEvent(QPaintEvent* event)
{
  QWebView::paintEvent(event);

  if (m_mousePos != QPoint(0, 0)) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect(0, 0, 20, 20);
    rect.moveCenter(m_mousePos);

    QPen pen(QColor(255, 255, 255, 100), 2);
    painter.setPen(pen);
    painter.setBrush(QColor(0, 0, 0, 100));
    painter.drawEllipse(rect);
  }
}

void
WebView::leaveEvent(QEvent*)
{
  qApp->restoreOverrideCursor();
  m_mousePos = QPoint(0, 0);
  update();
}

void
WebView::enterEvent(QEvent*)
{

  qApp->setOverrideCursor(QCursor(Qt::BlankCursor));
}
