#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql charts
QT += sql
QT += network
QT += serialport



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    arduino.cpp \
    contrats.cpp \
    mailer.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp
    arduino.cpp

HEADERS += \
    arduino.h \
    contrats.h \
    mailer.h \
    mainwindow.h \
    connection.h
    arduino.h

FORMS += \
    mainwindow.ui

# Include path for SQLite driver DLLs if needed
# Ajout optionnel si les drivers sont dans un dossier spécifique
# LIBS += -LC:/Qt/5.15.2/mingw81_64/plugins/sqldrivers

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

