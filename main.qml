import QtQuick 2.7
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import example.backend 1.0

ApplicationWindow {
    id: window
    width: 800
    height: 800
    visible: true

    BackEnd {
        id: backend
    }

    CircularGauge {
        value: backend.aoaValue
        anchors.centerIn: parent

        property bool accelerating: false

        Keys.onSpacePressed: accelerating = true
        Keys.onReleased: {
            if (event.key === Qt.Key_Space) {
                accelerating = false;
                event.accepted = true;
            }
        }

        Component.onCompleted: forceActiveFocus()

        Behavior on value {
            NumberAnimation {
                duration: 50
            }
        }
    }
}
