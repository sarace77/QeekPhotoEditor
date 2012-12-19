#ifndef QPEWORKAREAWIDGET_H
#define QPEWORKAREAWIDGET_H

#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

class QPEWorkAreaWidget : public QWidget
{
    Q_OBJECT
private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QLabel *_imageArea;

public:
    explicit QPEWorkAreaWidget(QWidget *parent = 0);
    ~QPEWorkAreaWidget();

public slots:
    void displayQImage(QImage image);

signals:
    void mouseButtonDoubleClicked(QPoint newPos);
    void mouseLeftButtonClicked(QPoint newPos);
    void mouseMiddleButtonClicked(QPoint newPos);
    void mouseMoved(QPoint newPos);
    void mouseRightButtonClicked(QPoint newPos);
};

#endif // QPEWORKAREAWIDGET_H
