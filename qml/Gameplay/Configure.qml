import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: configure
    anchors.fill: parent

    Component.onCompleted: {
        const args = {parentStackView: configureStackView}
        configureStackView.replace("Configure/Event.qml", args)
        rootWindow.minimumWidth = 500;
        rootWindow.minimumHeight = 350;
    }

    StackView{
        id: configureStackView
        anchors.fill: parent
        // initialItem: "Configure/Event.qml" // idk how to parse arguments/properies

        pushEnter: Transition{}
        pushExit: Transition{}
        popEnter: Transition{}
        popExit: Transition{}
        replaceEnter: Transition{}
        replaceExit: Transition{}
    }
}
