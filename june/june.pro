#-------------------------------------------------
#
# Project created by QtCreator 2020-03-04T18:34:25
#
#-------------------------------------------------

QT += core gui widgets

CONFIG += c++19
if(debug){
    CONFIG += console
}
CONFIG -= app_bundle
TEMPLATE = app

release: TARGET = june
debug: TARGET = juned

DESTDIR = $$(DEV_BIN)

release: BUILDDIR = build/release
debug:   BUILDDIR = build/debug

OBJECTS_DIR = $$BUILDDIR/.obj
MOC_DIR = $$BUILDDIR/.moc
RCC_DIR = $$BUILDDIR/.qrc
UI_DIR = $$BUILDDIR/.ui


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$(JUNE_ROOT)

if(debug){

    LIBS += -L$$(DEV_LIBS) -ltagsystemd
#LIBS += -ltagsystemd
}
else{
    LIBS += -L$$(DEV_LIBS) -ltagsystem
}


SOURCES += \
        app.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        app.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
