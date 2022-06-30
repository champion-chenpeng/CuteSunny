QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bbs.cpp \
    campus.cpp \
    comment.cpp \
    mainwindow.cpp \
    main.cpp \
    mywidget.cpp \
    treehole.cpp \
    smtp.cpp

HEADERS += \
    bbs.h \
    campus.h \
    comment.h \
    mainwindow.h \
    mywidget.h \
    treehole.h \
    smtp.h

FORMS += \
    bbs.ui \
    campus.ui \
    comment.ui \
    mainwindow.ui \
    mywidget.ui \
    treehole.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
