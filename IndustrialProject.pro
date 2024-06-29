QT       += core gui multimediawidgets multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    camerasql.cpp \
    filemanager.cpp \
    filereader.cpp \
    imglist.cpp \
    main.cpp \
    dialog.cpp \
    mcore.cpp \
    newsql.cpp \
    opencv.cpp \
    settingpage.cpp \
    systemconf.cpp \
    vertify_d.cpp

HEADERS += \
    camera.h \
    camerasql.h \
    dialog.h \
    filemanager.h \
    filereader.h \
    imglist.h \
    mcore.h \
    newsql.h \
    opencv.h \
    settingpage.h \
    systemconf.h \
    vertify_d.h

FORMS += \
    camera.ui \
    dialog.ui \
    imglist.ui \
    settingpage.ui \
    vertify_d.ui

INCLUDEPATH +=/home/eureka/CMAKEINSTALL/opencv/include/opencv4/
INCLUDEPATH +=/home/eureka/CMAKEINSTALL/onnxruntime-linux-x64-1.18.0/include/
LIBS +=/home/eureka/CMAKEINSTALL/opencv/lib/libopencv_*
LIBS +=/home/eureka/CMAKEINSTALL/onnxruntime-linux-x64-1.18.0/lib/libonnxruntime.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
