cmake_minimum_required(VERSION 3.16)

project(PetanqueTeam VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appPetanqueTeam
    main.cpp
)

qt_add_qml_module(appPetanqueTeam
    URI PetanqueTeam
    VERSION 1.0

    SOURCES cpp/Login.h cpp/Login.cpp
    SOURCES cpp/DoubleStartProtection.h cpp/DoubleStartProtection.cpp
    SOURCES cpp/Backend.h cpp/Backend.cpp
    SOURCES cpp/support/Log.h cpp/support/Log.cpp
    SOURCES cpp/support/LogQML.h cpp/support/LogQML.cpp
    SOURCES cpp/Event.h cpp/Event.cpp

    QML_FILES qml/Main.qml
    QML_FILES qml/Gameplay.qml
    QML_FILES qml/AppAlreadyRunning.qml
    QML_FILES qml/LoginForm.qml
    QML_FILES qml/Gameplay/Configure.qml
    QML_FILES qml/Gameplay/Continue.qml
    SOURCES cpp/Serializable.h cpp/Serializable.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPetanqueTeam PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPetanqueTeam
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPetanqueTeam
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appPetanqueTeam
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
