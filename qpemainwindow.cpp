#include "qpemainwindow.h"
#include "ui_qpemainwindow.h"

#include <QDebug>
#include <QMessageBox>

QPEMainWindow::QPEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPEMainWindow)
{
    ui->setupUi(this);
    ui->actionRestoreZoom->setEnabled(false);
    ui->actionSaveImage->setEnabled(false);
    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRestoreZoom->setEnabled(false);
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
    waMenu->addAction(ui->actionRestoreZoom);
    waMenu->addSeparator();
    waMenu->addAction(ui->actionAbout);
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

    zoomInCount = 0;
    zoomOutCount = 0;
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

void QPEMainWindow::on_actionAbout_triggered() {
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle("About QeekPhotoEditor");
    aboutBox.setText("<center><h1>Qeek PhotoEditor</h1><h2>0.1</h2><b>Written by:</b><br>Antonio Scopelliti<br>(<i>sarace77<i>)</center>");
    aboutBox.exec();
}

void QPEMainWindow::on_actionOpenImage_triggered() {
    imageDialog->show();
}

void QPEMainWindow::on_actionRestoreZoom_triggered() {
    zoomInCount = 0;
    zoomOutCount = 0;
    ui->actionRestoreZoom->setEnabled(false);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
    currentImage = loadedImage;
    emit availableImage(currentImage);
}

void QPEMainWindow::on_actionSaveImage_triggered() {
    saveDialog->show();
}

void QPEMainWindow::on_actionZoomIn_triggered() {
    ui->actionRestoreZoom->setEnabled(true);
    ui->actionZoomIn->setEnabled(++zoomInCount < 4);
    ui->actionZoomOut->setEnabled(true);
    if (zoomInCount != zoomOutCount) {
        currentImage = loadedImage.scaled(2 * currentImage.size(), Qt::KeepAspectRatio);
    } else {
        on_actionRestoreZoom_triggered();
    }
    emit availableImage(currentImage);
}

void QPEMainWindow::on_actionZoomOut_triggered() {
    ui->actionRestoreZoom->setEnabled(true);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(++zoomOutCount < 4);
    if (zoomInCount != zoomOutCount) {
        currentImage = loadedImage.scaled(0.5 * currentImage.size(), Qt::KeepAspectRatio);
    } else {
        on_actionRestoreZoom_triggered();
    }
    emit availableImage(currentImage);
}

void QPEMainWindow::onImageFileSelected() {
    QString selectedImage = imageDialog->selectedFiles().at(0);
    if (QFile(selectedImage).exists()) {
        loadedImage = QImage(selectedImage);
        currentImage = loadedImage;
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
