import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    id: rootWindow

    width: 1280
    height: 720
    visible: false

    // onWidthChanged: {
    //     console.log("w:" + width + " h:" + height)
    // }
    // onHeightChanged: {
    //     console.log("w:" + width + " h:" + height)
    // }

    Material.theme: Material.Dark

    Connections{
        target: DoubleStartProtection
        function onApplicationIsAlreadyRunning(){
            rootLoader.source = "ApplicationIsAlreadyRunning.qml" // sets own min height/width
        }

        function onVerified(){
            rootLoader.source = "LoginForm.qml" // sets own min height/width
        }
    }

    Connections{
        target: Login
        function onAuthenticated(){
            log.i("authenticated login" , "Main.qml -> onAuthenticated")
            Backend.memory.load()
        }
    }

    Connections{
        target: Backend
        function onRestartedEvent(){
            Backend.event.goToNextStage() // from Stage None to Configure
            rootLoader.source = "Gameplay.qml"
        }
    }

    Connections{
        target: Backend.memory
        function onMemoryFileNotExist(){
            Backend.event.goToNextStage(); // from Stage None to Configure
            rootLoader.source = "Gameplay.qml";
        }

        function onMemoryLoaded(){
            rootLoader.source = "Gameplay.qml"
        }

        function onMemoryLoadError(message){
            // open page with "cannot start application" and display current session from Logs
            let title = "Error while loading Memory!"
            rootLoader.setSource("ErrorPage.qml", { pageTitle: title, pageMessage: message })
            log.e("error occur while loading memory: " + message, this.target.toString() + " onMemoryLoadError")
        }

        function onMemorySaved(){
            // send to server
        }

        function onMemorySaveError(message){
            log.w("error occur while saving memory: " + message)
        }
    }


    Loader{
        id: rootLoader
        anchors.fill: parent
        onLoaded: {
            rootWindow.visible = true
        }
    }

}
