#include "qpeopencvwrapper.h"

QPEOpenCVWrapper::QPEOpenCVWrapper()
{
}

Mat QPEOpenCVWrapper::qimage2mat(QImage image) {
    int type = CV_8UC3;
    switch(image.depth()) {
    case 8:
        type = CV_8UC1;
        break;
    case 16:
        type = CV_16UC1;
        break;
    case 32:
        type = CV_8UC4;
        break;
    }
    Mat result = Mat(image.height(), image.width(), type, (void*) image.constBits());
    return result.clone();
}

QImage QPEOpenCVWrapper::mat2qimage(Mat image) {
    QImage::Format  imgFormat = QImage::Format_RGB888;

    switch(image.type()) {
    case CV_8UC1:
        imgFormat = QImage::Format_Indexed8;
        break;
    case CV_8UC4:
        imgFormat = QImage::Format_ARGB32;
        break;
    case CV_16UC1:
        imgFormat = QImage::Format_RGB16;
        break;
    default:
        break;
    }
    return QImage(image.data, image.cols, image.rows, image.step, imgFormat);
}
