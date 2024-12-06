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
            rootLoader.source = "ApplicationIsAlreadyRunning.qml"
        }

        function onVerified(){
            rootLoader.source = "LoginForm.qml"
        }
    }

    Connections{
        target: Login
        function onAuthenticated(){
            Memory.load()
        }
        function onAuthenticationFailed(){
            log.e("onAuthenticationFailed") // display popup
        }
    }

    Connections{
        target: Memory
        function onMemoryFileNotExist(){
            Backend.event.goToNextStage() // from Stage None to Configure
            rootLoader.source = "Play.qml"
        }

        function onMemoryLoaded(){
            rootLoader.source = "Play.qml"
        }

        function onMemoryLoadError(message){
            rootLoader.source = ""
            log.e("error occur while loading memory: " + message, this.target.toString() + " onMemoryLoadError")
        }

        function onMemorySaved(reload){ // not reloading memory, while exiting the app
            // console.log("memory saved");
            // if(reload)
                // Memory.load()
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
