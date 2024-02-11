import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0

Item {

    property alias customStyle : gauge.style
    property alias value : gauge.value
    property alias minVal : gauge.minimumValue
    property alias maxVal : gauge.maximumValue
    property alias valStr : valText.text
    property string myName: "Gauge"

    Layout.fillWidth:true
    Layout.minimumHeight: 100
    Layout.minimumWidth: 100
    Layout.preferredHeight: 350
    Layout.preferredWidth: 450

    ColumnLayout {
        id: cLayout
        spacing: 5

        Text {
            text: myName
            color: "white"
            Layout.alignment: Qt.AlignCenter
            font.pointSize: 20
        }

        CircularGauge {
            id: gauge
            Layout.alignment: Qt.AlignCenter

            Behavior on value {
                NumberAnimation {
                    duration: 150
                }
            }
        }

        Text {
            id: valText
            Layout.alignment: Qt.AlignCenter
            color: "white"
            font.pointSize: 15
        }
    }
}
