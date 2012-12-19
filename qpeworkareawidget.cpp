#include "qpeworkareawidget.h"

#include <QDebug>

QPEWorkAreaWidget::QPEWorkAreaWidget(QWidget *parent) :
    QWidget(parent)
{
    _imageArea = new QLabel(this);
    _imageArea->setGeometry(0, 0, 10, 10);
    _imageArea->setMouseTracking(true);
}

QPEWorkAreaWidget::~QPEWorkAreaWidget() {
    delete _imageArea;
}

void QPEWorkAreaWidget::displayQImage(QImage image) {
    resize(image.size());
    _imageArea->resize(image.size());
    _imageArea->setPixmap(QPixmap::fromImage(image));
}

void QPEWorkAreaWidget::mousePressEvent(QMouseEvent *event) {
    switch(event->button()) {
    case Qt::LeftButton:
        emit mouseLeftButtonClicked(event->pos());
        break;
    case Qt::MiddleButton:
        emit mouseMiddleButtonClicked(event->pos());
        break;
    case Qt::RightButton:
        emit mouseRightButtonClicked(event->pos());
        break;
    default:
        break;
    }
}

void QPEWorkAreaWidget::mouseReleaseEvent(QMouseEvent *event) {

}

void QPEWorkAreaWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    emit mouseButtonDoubleClicked(event->pos());
}

void QPEWorkAreaWidget::mouseMoveEvent(QMouseEvent *event) {
    emit mouseMoved(event->pos());
}
