#-------------------------------------------------
#
# Project created by QtCreator 2020-02-12T22:35:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = identify
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h \
    base/base.h \
    base/base64.h \
    base/http.h \
    base/utils.h \
    ocr.h


INCLUDEPATH +=  /usr/local/curl/include                     \
                /usr/local/json/include                     \
                /usr/local/openssl/include                  \
                /usr/local/opencv-2.4.9/include             \
                /usr/local/opencv-2.4.9/include/opencv      \
                /usr/local/opencv-2.4.9/include/opencv2     \



LIBS +=   /usr/local/curl/lib/libcurl.so.4.5.0        \
          /usr/local/json/lib/libjsoncpp.so           \
          /usr/local/openssl/lib/libssl.so.1.0.0      \
         /usr/local/openssl/lib/libcrypto.so.1.0.0   \
         /usr/local/opencv-2.4.9/lib/libopencv*       \
         /usr/local/opencv-2.4.9/lib/libv4l1*         \
         /usr/local/opencv-2.4.9/lib/libv4l2*        \
         /usr/local/opencv-2.4.9/lib/libv4lc*        \

FORMS += \
        widget.ui

RESOURCES +=
