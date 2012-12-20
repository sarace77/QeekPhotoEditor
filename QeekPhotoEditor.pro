#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T10:37:57
#
#-------------------------------------------------

QT       += core gui

TARGET = QeekPhotoEditor
TEMPLATE = app


SOURCES += main.cpp\
        qpemainwindow.cpp \
    qpeworkareawidget.cpp \
    qpeopencvwrapper.cpp

HEADERS  += qpemainwindow.h \
    qpeworkareawidget.h \
    qpeopencvwrapper.h

FORMS    += qpemainwindow.ui

RESOURCES += \
    qperesources.qrc


LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
