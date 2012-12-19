#include "qpemainwindow.h"
#include "ui_qpemainwindow.h"

#include <QDebug>

QPEMainWindow::QPEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPEMainWindow)
{
    ui->setupUi(this);
    imageDialog = new QFileDialog();

    workArea = new QPEWorkAreaWidget(ui->centralWidget);
    workArea->resize(ui->centralWidget->size());

    connect(imageDialog, SIGNAL(accepted()), this, SLOT(onImageFileSelected()));

    connect(workArea, SIGNAL(mouseMoved(QPoint)), this, SLOT(_DEBUG_showPointerPos(QPoint)));
    connect(workArea, SIGNAL(mouseButtonDoubleClicked(QPoint)), this, SLOT(_DEBUG_showPointerPos(QPoint)));
    connect(workArea, SIGNAL(mouseLeftButtonClicked(QPoint)), this, SLOT(_DEBUG_showPointerPos(QPoint)));

    connect(this, SIGNAL(availableImage(QImage)), workArea, SLOT(displayQImage(QImage)));
}

QPEMainWindow::~QPEMainWindow()
{
    delete imageDialog;
    delete workArea;
    delete ui;
}

void QPEMainWindow::_DEBUG_showPointerPos(QPoint newPos) {
    ui->statusBar->showMessage(QString("%1,%2").arg(newPos.x()).arg(newPos.y()));
}

void QPEMainWindow::on_actionOpenImage_triggered() {
    imageDialog->show();
}

void QPEMainWindow::onImageFileSelected() {

    QString selectedImage = imageDialog->selectedFiles().at(0);
    if (QFile(selectedImage).exists()) {
        currentImage = QImage(selectedImage);
        if (currentImage.size().width() > this->size().width() || currentImage.size().height() > this->size().height() )
            resize(currentImage.size().width(), currentImage.size().height() + 60);
        emit availableImage(currentImage);
        workArea->setMouseTracking(true);
    }
}
