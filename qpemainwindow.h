#ifndef QPEMAINWINDOW_H
#define QPEMAINWINDOW_H

#include <QImage>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>

#include "qpeworkareawidget.h"

namespace Ui {
class QPEMainWindow;
}

class QPEMainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    Ui::QPEMainWindow *ui;
    QFileDialog *imageDialog, *saveDialog;
    QPEWorkAreaWidget *workArea;

    QImage currentImage;
    QMenu *waMenu;

    void resizeEvent ( QResizeEvent *rEvent );

private slots:
    void _DEBUG_showPointerPos(QPoint newPos);

    void changeWorkingAreaSize(QSize size);
    void on_actionOpenImage_triggered();
    void on_actionSaveImage_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void onImageFileSelected();
    void onSaveDialogAccepted();

public:
    explicit QPEMainWindow(QWidget *parent = 0);
    ~QPEMainWindow();
    
signals:
    void availableImage(QImage image);
    void sizeChanged(QSize size);
};

#endif // QPEMAINWINDOW_H
