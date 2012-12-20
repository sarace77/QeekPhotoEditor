#include "qpeworkareawidget.h"

#include <QDebug>
#include <QScrollBar>


QPEWorkAreaWidget::QPEWorkAreaWidget(QWidget *parent) :
    QScrollArea(parent)
{
    _parent = parent;

    setBackgroundRole(QPalette::Window);

    _imageArea = new QLabel();
    _imageArea->setAlignment(Qt::AlignCenter);
    _imageArea->setBackgroundRole(QPalette::Window);
//    _imageArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    _imageArea->setScaledContents(true);
    _imageArea->setMouseTracking(true);
    _waMenu = NULL;
    setWidget(_imageArea);

}

QPEWorkAreaWidget::~QPEWorkAreaWidget() {
    delete _imageArea;
}

void QPEWorkAreaWidget::contextMenuEvent(QContextMenuEvent *event) {
    if (_waMenu != NULL) {
        _waMenu->exec(event->globalPos());
    }
}

void QPEWorkAreaWidget::displayQImage(QImage image) {
    if (_parent != NULL) {
        resize(_parent->size());
    }
    setWidgetResizable(image.width() < _parent->width() && image.height() < _parent->height());
    _imageArea->setPixmap(QPixmap::fromImage(image));
    _imageArea->adjustSize();
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

void QPEWorkAreaWidget::setMenu(QMenu *menu) {
    _waMenu = menu;
}
