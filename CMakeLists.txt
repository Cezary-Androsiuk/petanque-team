cmake_minimum_required(VERSION 3.16)

project(PetanqueTeam VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appPetanqueTeam
    cpp/main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/cpp)

qt_add_qml_module(appPetanqueTeam
    URI PetanqueTeam
    VERSION 1.0

    SOURCES cpp/Login.h cpp/Login.cpp
    SOURCES cpp/DoubleStartProtection.h cpp/DoubleStartProtection.cpp
    SOURCES cpp/Backend.h cpp/Backend.cpp
    SOURCES cpp/Serializable.h cpp/Serializable.cpp
    SOURCES cpp/DebugConstraints.h
    SOURCES cpp/SingletonManager.h cpp/SingletonManager.cpp
    ################################
    SOURCES cpp/storages/Memory.h cpp/storages/Memory.cpp
    SOURCES cpp/storages/DefaultPersonalizationData.h cpp/storages/DefaultPersonalizationData.cpp
    SOURCES cpp/storages/Personalization.h cpp/storages/Personalization.cpp
    ################################
    SOURCES cpp/support/Log.h cpp/support/Log.cpp
    SOURCES cpp/support/LogQML.h cpp/support/LogQML.cpp
    SOURCES cpp/support/LogSession.h cpp/support/LogSession.cpp
    SOURCES cpp/support/LogSessionPart.h cpp/support/LogSessionPart.cpp
    ################################
    SOURCES cpp/objects/Event.h cpp/objects/Event.cpp
    SOURCES cpp/objects/Phase.h cpp/objects/Phase.cpp
    SOURCES cpp/objects/SubPhase.h cpp/objects/SubPhase.cpp
    SOURCES cpp/objects/Team.h cpp/objects/Team.cpp
    SOURCES cpp/objects/Player.h cpp/objects/Player.cpp
    SOURCES cpp/objects/Round.h cpp/objects/Round.cpp
    SOURCES cpp/objects/Match.h cpp/objects/Match.cpp
    SOURCES cpp/objects/MatchTypeBase.h cpp/objects/MatchTypeBase.cpp
    SOURCES cpp/objects/MatchSingiels.h cpp/objects/MatchSingiels.cpp
    SOURCES cpp/objects/MatchDublets.h cpp/objects/MatchDublets.cpp
    SOURCES cpp/objects/MatchTriplets.h cpp/objects/MatchTriplets.cpp
    SOURCES cpp/objects/GroupMatch.h cpp/objects/GroupMatch.cpp
    SOURCES cpp/objects/GroupSelection.h cpp/objects/GroupSelection.cpp
    ################################
    SOURCES cpp/enums/GenderEnum.h cpp/enums/GenderEnum.cpp
    SOURCES cpp/enums/AgeGroupEnum.h cpp/enums/AgeGroupEnum.cpp
    SOURCES cpp/enums/StageEnum.h cpp/enums/StageEnum.cpp
    SOURCES cpp/enums/PhaseEnum.h cpp/enums/PhaseEnum.cpp
    SOURCES cpp/enums/RoundStageEnum.h cpp/enums/RoundStageEnum.cpp



    QML_FILES qml/Main.qml
    QML_FILES qml/Gameplay.qml
    QML_FILES qml/AppAlreadyRunning.qml
    QML_FILES qml/LoginForm.qml
    QML_FILES qml/ErrorPage.qml
    ################################ Popups
    QML_FILES qml/Popups/ConfirmNextPopup.qml
    QML_FILES qml/Popups/InfoPopup.qml
    ################################ Configure
    QML_FILES qml/Gameplay/Configure.qml
    QML_FILES qml/Gameplay/Configure/Event.qml
    QML_FILES qml/Gameplay/Configure/InfoField.qml
    QML_FILES qml/Gameplay/Configure/TeamsList.qml
    QML_FILES qml/Gameplay/Configure/Player.qml
    QML_FILES qml/Gameplay/Configure/PlayerDelegate.qml
    QML_FILES qml/Gameplay/Configure/Team.qml
    QML_FILES qml/Gameplay/Configure/TeamDelegate.qml
    ################################ Play
    QML_FILES qml/Gameplay/Play.qml
    QML_FILES qml/Gameplay/Settings.qml
    QML_FILES qml/Gameplay/Play/Phase.qml
    QML_FILES qml/Gameplay/Play/SubPhase.qml
    QML_FILES qml/Gameplay/Play/Match.qml
    QML_FILES qml/Gameplay/Play/Matches.qml
    QML_FILES qml/Gameplay/Play/Match/GroupSelection.qml
    QML_FILES qml/Gameplay/Play/Match/GroupMatch.qml
    QML_FILES qml/Gameplay/Play/Match/MatchType/SelectionHalf.qml
    QML_FILES qml/Gameplay/Play/Match/MatchType/MatchHalf.qml
    QML_FILES qml/Gameplay/Play/RoundSummary.qml
    QML_FILES qml/Gameplay/Play/RoundSummary/Summary.qml
    QML_FILES qml/Gameplay/Play/RoundSummary/Ranking.qml
    ################################ Finish
    QML_FILES qml/Gameplay/Finish.qml
    QML_FILES qml/Popups/AskPopup.qml
    QML_FILES

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
