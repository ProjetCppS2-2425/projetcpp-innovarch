QT       += core gui sql widgets charts printsupport

CONFIG += c++17

# SOURCES
SOURCES += \
    architechtes.cpp \
    connection.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp

# HEADERS
HEADERS += \
    architechtes.h \
    connection.h \
    dialog.h \
    mainwindow.h

# FORMS
FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += core gui widgets printsupport
CONFIG += c++17
QT += serialport
