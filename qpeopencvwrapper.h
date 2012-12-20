#ifndef QPEOPENCVWRAPPER_H
#define QPEOPENCVWRAPPER_H

#include <opencv2/core/core.hpp>

#include <QImage>

using namespace cv;

class QPEOpenCVWrapper
{
public:
    QPEOpenCVWrapper();

    static Mat qimage2mat(QImage image);
    static QImage mat2qimage(Mat image);
};

#endif // QPEOPENCVWRAPPER_H
