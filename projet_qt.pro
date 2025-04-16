QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet_qt
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    projetcrud.cpp \
    projet.cpp

HEADERS  += mainwindow.h \
    projetcrud.h \
    projet.h

FORMS    += mainwindow.ui \
    projetcrud.ui

RESOURCES += \
    ressources.qrc