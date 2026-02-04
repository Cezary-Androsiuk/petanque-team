import QtQuick
import QtQuick.Controls.Material

import "Trace.js" as Trace

ApplicationWindow {
    id: rootWindow

    width: 1280
    height: 720
    visible: false

    Material.theme: Material.Dark

    /// Focus tracker START
    // property Item currentFocusItem: activeFocusItem

    // Binding {
    //     target: null
    //     property: "currentFocusItem"
    //     value: Window.activeFocusItem
    //     delayed: true
    // }

    // onCurrentFocusItemChanged: {
    //     var strFocusText = "GUI focus was changed to: " + currentFocusItem
    //     log.i(strFocusText, "Main.qml onCurrentFocusItemChanged");
    // }
    /// Focus tracker END

    Connections{
        target: DoubleStartProtection
        function onApplicationIsAlreadyRunning(){ Trace.t();
            rootLoader.source = "AppAlreadyRunning.qml" // sets own min height/width
        }

        function onVerified(){ Trace.t();
            rootLoader.source = "LoginForm.qml" // sets own min height/width
            // rootWindow.showMaximized();
        }
    }

    Connections{
        target: Backend.login
        function onAuthenticated(){ Trace.t();
            log.i("authenticated login" , "Main.qml -> onAuthenticated")
            Backend.memory.load()
        }
    }

    Connections{
        target: Backend
        function onRestartedEvent(){ Trace.t();
            Backend.event.goToNextStage() // from Stage None to Configure
            rootLoader.source = "Gameplay.qml"
        }
    }

    Connections{
        target: Backend.memory
        function onMemoryFileNotExist(){ Trace.t();
            Backend.event.goToNextStage(); // from Stage None to Configure
            rootLoader.source = "Gameplay.qml";
        }

        function onMemoryLoaded(){ Trace.t();
            rootLoader.source = "Gameplay.qml"
        }

        function onMemoryLoadError(message){ Trace.t(message);
            // open page with "cannot start application" and display current session from Logs
            let title = "Błąd ładowania pamięci!"
            rootLoader.setSource("ErrorPage.qml", { pageTitle: title, pageMessage: message })
            log.e("error occur while loading memory: " + message, this.target.toString() + " onMemoryLoadError")
        }

        function onMemorySaved(){ Trace.t();
            // send to server
        }

        function onMemorySaveError(message){ Trace.t(message);
            log.w("error occur while saving memory: " + message)
        }
    }


    Loader{
        id: rootLoader
        anchors.fill: parent
        onLoaded: { Trace.t();
            rootWindow.visible = true
        }
    }



    Rectangle{
        id: rootWindowPopupDimmer
        anchors.fill: parent

        readonly property double dimmerOpacity: 0.8

        function show(){ Trace.t();
            opacity = dimmerOpacity;
        }
        function hide(){ Trace.t();
            opacity = 0;
        }

        color: Qt.rgba(28/255, 27/255, 31/255)
        opacity: 0

        Behavior on opacity { NumberAnimation { duration: 150 } }
    }

    Item{
        id: rootWindowCenterPopupAnchor
        anchors.fill: parent
    }
}
