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
