#-------------------------------------------------
#
# Project created by QtCreator 2020-11-01T19:45:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SliceView
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

CONFIG += c++17

SOURCES += \
    main.cpp \
    widget.cpp \
    flowlayout.cpp \
    visuallistelement.cpp \
    visualcategory.cpp \
    visualcategorylistelement.cpp \
    emptyitemdelegate.cpp \
    visualcontainer.cpp \
    external/MultPages.cpp \
    external/ScreenPage.cpp \
    derivative.cpp \
    visualstackelement.cpp \
    touchinterfacing.cpp \
    swipinggesture.cpp \
    touchsystem.cpp \
    restraintscrollarea.cpp \
    restraintscrollareabg.cpp \
    ios.cpp

HEADERS += \
    widget.h \
    flowlayout.h \
    structures.h \
    visuallistelement.h \
    visualcategory.h \
    visualcategorylistelement.h \
    emptyitemdelegate.h \
    visualcontainer.h \
    external/MultPages.hpp \
    external/ScreenPage.hpp \
    derivative.h \
    visualstackelement.h \
    touchinterfacing.h \
    swipinggesture.h \
    touchsystem.h \
    restraintscrollarea.h \
    restraintscrollareabg.h \
    ios.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

FORMS += \
    form.ui
