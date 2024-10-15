QT       += core gui multimedia widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    camera_setting.cpp \
    camerasql.cpp \
#    filemanager.cpp \
#    filereader.cpp \
    clwidget.cpp \
    imgcl.cpp \
    main.cpp \
    dialog.cpp \
    mainpage.cpp \
    mcore.cpp \
    n_filereader.cpp \
    settingpage.cpp \
    sql_filereader.cpp \
    systemconf.cpp \
    vertify_d.cpp

HEADERS += \
    camera.h \
    camera_setting.h \
    camerasql.h \
    clwidget.h \
    dialog.h \
#    filemanager.h \
#    filereader.h \
    imgcl.h \
    mainpage.h \
    mcore.h \
    n_filereader.h \
    settingpage.h \
    sql_filereader.h \
    systemconf.h \
    vertify_d.h

FORMS += \
    camera.ui \
    camera_setting.ui \
    dialog.ui \
    imgcl.ui \
    mainpage.ui \
    settingpage.ui \
    vertify_d.ui
#//@9-10
#INCLUDEPATH +=/home/eureka/CMAKEINSTALL/opencv/include/opencv4/
#INCLUDEPATH +=/home/eureka/CMAKEINSTALL/onnxruntime-linux-x64-1.18.0/include/
#LIBS +=/home/eureka/CMAKEINSTALL/opencv/lib/libopencv_*
#LIBS +=/home/eureka/CMAKEINSTALL/onnxruntime-linux-x64-1.18.0/lib/libonnxruntime.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
