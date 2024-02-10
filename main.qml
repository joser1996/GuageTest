import QtQuick 2.7
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import example.backend 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: window
    width: 910
    height: 460
    visible: true
    minimumHeight: 110
    minimumWidth: 210
    maximumHeight: 470
    maximumWidth: 910
    BackEnd {
        id: backend
    }


    RowLayout{
        anchors.fill: parent
        spacing: 8

        CircularGauge {
            id: aoa
            value: backend.aoaValue
            Layout.fillWidth:true
            Layout.fillHeight: true
            Layout.minimumHeight: 100
            Layout.minimumWidth: 100
            Layout.preferredHeight: 450
            Layout.preferredWidth: 450


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

        CircularGauge {
            id: aos
            value: backend.aoaValue
            Layout.fillWidth:true
            Layout.fillHeight: true
            Layout.minimumHeight: 100
            Layout.minimumWidth: 100
            Layout.preferredHeight: 450
            Layout.preferredWidth: 450
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
}
