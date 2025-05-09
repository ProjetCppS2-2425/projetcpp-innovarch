cmake_minimum_required(VERSION 3.16)

project(GestionRessources VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts Multimedia SerialPort)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        gestionressources.cpp
        gestionressources.h
        connection.cpp rec.h
        rec.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GestionRessources
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        icons.qrc
        Atelier_Connexion.pro
        Atelier_Connexion.pro.user
        connection.h
        IconDelegate.h
        rec.h
        rec.cpp
        arduino.cpp
        arduino.h
        architechtes.h dialog.h
        architechtes.cpp dialog.cpp
        dialog.ui
        projetcrud.cpp projetcrud.h
        arduinocl.h arduinocl.cpp
        sms.h sms.cpp
        sms.h sms.cpp
        clients.h clients.cpp
        contracteur.cpp
        contracteur.h
        arduinocontracteur.cpp
        arduinocontracteur.h
        ../../../Downloads/youssef/projetcpp-innovarch-gestion-contrats/arduino.h ../../../Downloads/youssef/projetcpp-innovarch-gestion-contrats/contrats.h ../../../Downloads/youssef/projetcpp-innovarch-gestion-contrats/mailer.h
        contrats.h contrats.cpp
        mailer.h mailer.cpp
        arduinocontrat.h arduinocontrat.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GestionRessources APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GestionRessources SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GestionRessources
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GestionRessources PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::SerialPort)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GestionRessources)
endif()
set_target_properties(GestionRessources PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GestionRessources
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GestionRessources)
endif()
