#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QWebView>

class WebView : public QWebView
{
  Q_OBJECT
public:
  explicit WebView(QWidget* parent);
  ~WebView();

protected:
  virtual void leaveEvent(QEvent* event);
  virtual void enterEvent(QEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void paintEvent(QPaintEvent* event);

private:
  QPoint m_mousePos;
};

#endif // WEBVIEW_H
