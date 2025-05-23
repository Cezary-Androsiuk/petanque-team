import QtQuick
import QtQuick.Controls.Material

Item {
    id: loginForm
    anchors.fill: parent

    property int targetWidth: 230
    property int targetHeight: 260

    Component.onCompleted: {
        rootWindow.minimumWidth = targetWidth + 50;
        rootWindow.minimumHeight = targetHeight + 50;
    }

    Connections{
        target: Backend.login
        function onAuthenticationFailed(message){
            log.i("Received failed authentication signal: " + message)
            errorInfoLabel.visible = true
            errorInfoLabel.text = message
        }
    }

    MouseArea{
        id: looseFocus
        anchors.fill: parent
        onClicked:{
            loginForm.focus = true
        }
    }

    Item{
        id: centeredField
        // anchors.centerIn: parent
        anchors{
            fill: parent
            leftMargin: (loginForm.width - targetWidth) * 0.5
            rightMargin: (loginForm.width - targetWidth) * 0.5
            topMargin: (loginForm.height - targetHeight) * 0.4
            bottomMargin: (loginForm.height - targetHeight) * 0.6
        }

        TextField{
            id: loginTextField
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 60

            placeholderText: qsTr("Login")
        }

        TextField{
            id: passwordTextField
            anchors{
                top: loginTextField.bottom
                topMargin: 10
                left: parent.left
                right: parent.right
            }
            height: 60

            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
        }

        CheckBox{
            id: showPasswordCheckBox
            anchors{
                top: passwordTextField.bottom
                left: passwordTextField.left
            }

            checked: false
            text: qsTr("Show Password")
            onCheckedChanged: {
                passwordTextField.echoMode =
                        checked ? TextInput.Normal : TextInput.Password;
            }
        }

        Label{
            id: errorInfoLabel
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: loginButton.top
            }
            visible: true
            color: Qt.rgba(0.8, 0.3, 0.3)
        }

        Button{
            id:  loginButton
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            width: 150
            height: 60

            text: qsTr("Login")
            onClicked:{
                var login = loginTextField.text;
                var password = passwordTextField.text;

                errorInfoLabel.visible = false

                if(Backend.isDebugMode)
                {
                    if(login === "") login = "example login";
                    if(password === "") password = "example password";
                }

                Backend.login.authenticate(login, password)
            }
        }

        Button{
            id:  loginNoMemoryButton
            anchors{
                top: loginButton.bottom
                topMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            width: 180
            height: 60

            visible: {
                if(Backend.isDebugMode && Backend.memory)
                    Backend.memory.debugMemoryFileExist();
                else
                    false;
            }

            text: qsTr("Login No Memory")
            onClicked:{
                Backend.memory.debugDeleteMemory();

                var login = loginTextField.text;
                var password = passwordTextField.text;

                errorInfoLabel.visible = false

                if(Backend.isDebugMode)
                {
                    if(login === "") login = "example login";
                    if(password === "") password = "example password";
                }

                Backend.login.authenticate(login, password)
            }
        }

    }
}
