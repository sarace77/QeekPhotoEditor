#ifndef QPEWORKAREAWIDGET_H
#define QPEWORKAREAWIDGET_H

#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPoint>
#include <QScrollArea>

class QPEWorkAreaWidget : public QScrollArea
{
    Q_OBJECT
private:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QLabel *_imageArea;
    QWidget *_parent;
    QMenu *_waMenu;

public:
    explicit QPEWorkAreaWidget(QWidget *parent = 0);
    ~QPEWorkAreaWidget();

    void setMenu(QMenu *menu);

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
