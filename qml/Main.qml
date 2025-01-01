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
            Backend.memory.load()
        }
        function onAuthenticationFailed(){
            log.i("onAuthenticationFailed") // display popup
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
            rootLoader.source = "" // open error page with what goes wrong and button to remove memory file or retry
            log.e("error occur while loading memory: " + message, this.target.toString() + " onMemoryLoadError")
        }

        function onMemorySaved(reload){ // not reloading memory, while exiting the app
            // console.log("memory saved");
            // if(reload)
                // Backend.memory.load()
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
