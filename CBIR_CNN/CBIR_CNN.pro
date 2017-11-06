#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T21:54:26
#
#-------------------------------------------------

QT       += core gui
CONFIG +=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CBIR_CNN
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
        mainwindow.cpp \
    computedistance.cpp \
    extracthash.cpp \
    knngraph.cpp

HEADERS += \
        mainwindow.h \
    extracthash.h \
    compute_distance.h \
    qt_kgraph.h

FORMS += \
        mainwindow.ui

INCLUDEPATH +=/home/liangshengwen/DeepBinaryCode/Caffe-DeepBinaryCode-master/include \
              /home/liangshengwen/DeepBinaryCode/Caffe-DeepBinaryCode-master/build/src \
              /usr/local/include/opencv /usr/local/include/opencv2 \
              /usr/local/cuda/include /usr/local/cuda/targets/X86_64-linux/include \
              /home/liangshengwen/kgraph/kgraph_hamming/kgraph  \

LIBS += -L/home/liangshengwen/DeepBinaryCode/Caffe-DeepBinaryCode-master/build/lib -lcaffe -lcblas -latlas -lglog
LIBS  +=-L/home/liangshengwen/anaconda2/lib
LIBS+= -L/usr/local/lib -lglog -lgflags -lleveldb -lsnappy -llmdb -lboost_system -lhdf5_hl -lhdf5 -lm -lopencv_core -lopencv_highgui -lopencv_imgproc -lboost_thread -lstdc++  -lpthread -lopencv_imgcodecs
INCLUDEPATH +=/home/liangshengwen/anaconda2/include /home/liangshengwen/anaconda2/include/python2.7
INCLUDEPATH +=/usr/include/
LIBS +=-L/home/liangshengwen/kgraph/kgraph_hamming/kgraph -lkgraph
LIBS += -lboost_python -lpython2.7 -lboost_system -lboost_timer

DISTFILES +=
