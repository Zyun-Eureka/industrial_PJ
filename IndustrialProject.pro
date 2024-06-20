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
    main.cpp \
    dialog.cpp \
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
    opencv.h \
    settingpage.h \
    systemconf.h \
    vertify_d.h

FORMS += \
    camera.ui \
    dialog.ui \
    settingpage.ui \
    vertify_d.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
