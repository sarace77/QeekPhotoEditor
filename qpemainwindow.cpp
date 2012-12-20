#include "qpemainwindow.h"
#include "ui_qpemainwindow.h"

#include <QDebug>

QPEMainWindow::QPEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPEMainWindow)
{
    ui->setupUi(this);
    ui->actionRestoreZoom->setEnabled(false);
    ui->actionSaveImage->setEnabled(false);
    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->mainToolBar->addAction(ui->actionOpenImage);
    ui->mainToolBar->addAction(ui->actionSaveImage);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionZoomIn);
    ui->mainToolBar->addAction(ui->actionZoomOut);
    ui->mainToolBar->addAction(ui->actionRestoreZoom);


    imageDialog = new QFileDialog();
    saveDialog = new QFileDialog();

    waMenu = new QMenu("Application Menu");
    waMenu->addAction(ui->actionOpenImage);
    waMenu->addAction(ui->actionSaveImage);
    waMenu->addSeparator();
    waMenu->addAction(ui->actionZoomIn);
    waMenu->addAction(ui->actionZoomOut);
    waMenu->addSeparator();
    waMenu->addAction(ui->actionExit);

    workArea = new QPEWorkAreaWidget(ui->centralWidget);
    workArea->resize(ui->centralWidget->size());
    workArea->setMenu(waMenu);

    connect(imageDialog, SIGNAL(accepted()), this, SLOT(onImageFileSelected()));
    connect(saveDialog, SIGNAL(accepted()), this, SLOT(onSaveDialogAccepted()));

    connect(workArea, SIGNAL(mouseMoved(QPoint)), this, SLOT(_DEBUG_showPointerPos(QPoint)));
    connect(workArea, SIGNAL(mouseButtonDoubleClicked(QPoint)), this, SLOT(_DEBUG_showPointerPos(QPoint)));
    connect(workArea, SIGNAL(mouseLeftButtonClicked(QPoint)), this, SLOT(_DEBUG_showPointerPos(QPoint)));

    connect(this, SIGNAL(availableImage(QImage)), workArea, SLOT(displayQImage(QImage)));
    connect(this, SIGNAL(sizeChanged(QSize)), this, SLOT(changeWorkingAreaSize(QSize)));
}

QPEMainWindow::~QPEMainWindow()
{
    delete imageDialog;
    delete saveDialog;
    delete workArea;
    delete waMenu;
    delete ui;
}

void QPEMainWindow::_DEBUG_showPointerPos(QPoint newPos) {
    ui->statusBar->showMessage(QString("%1,%2").arg(newPos.x()).arg(newPos.y()));
}

void QPEMainWindow::changeWorkingAreaSize(QSize size) {
    workArea->resize(size.width(), size.height() - 76);
    currentImage.scaled(size, Qt::KeepAspectRatio);
    emit availableImage(currentImage);
}


void QPEMainWindow::on_actionOpenImage_triggered() {
    imageDialog->show();
}

void QPEMainWindow::on_actionSaveImage_triggered() {
    saveDialog->show();
}

void QPEMainWindow::on_actionZoomIn_triggered() {
    currentImage = currentImage.scaled(2 * currentImage.size(), Qt::KeepAspectRatio);
    emit availableImage(currentImage);
}

void QPEMainWindow::on_actionZoomOut_triggered() {
    currentImage = currentImage.scaled(0.5 * currentImage.size(), Qt::KeepAspectRatio);
    emit availableImage(currentImage);
}

void QPEMainWindow::onImageFileSelected() {
    QString selectedImage = imageDialog->selectedFiles().at(0);
    if (QFile(selectedImage).exists()) {
        currentImage = QImage(selectedImage);
        if (currentImage.size().width() != this->size().width() || currentImage.size().height() != this->size().height() ) {
            resize(currentImage.width() + 32 , currentImage.height() + 92);
        }
        emit availableImage(currentImage);
        workArea->setMouseTracking(true);
        ui->actionSaveImage->setEnabled(true);
        ui->actionZoomIn->setEnabled(true);
        ui->actionZoomOut->setEnabled(true);
    }
}

void QPEMainWindow::onSaveDialogAccepted() {
    currentImage.save(saveDialog->selectedFiles().at(0));
}

void QPEMainWindow::resizeEvent(QResizeEvent *rEvent) {
    emit sizeChanged(rEvent->size());
}
