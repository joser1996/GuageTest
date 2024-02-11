import QtQuick 2.7
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: window
    width: 910
    height: 360
    visible: true
    maximumHeight: 370
    maximumWidth: 910
    background: Rectangle {
        anchors.fill: parent
        color:backend.bColor
    }

    RowLayout{
        anchors.fill: parent
        spacing: 8

        CustomGauge {
            id: aoa
            myName: "AoA"
            value: backend.aoaValue

            minVal: backend.aoaGauge.minValue
            maxVal: backend.aoaGauge.maxValue

            customStyle: CircularGaugeStyle {
                minimumValueAngle: backend.aoaGauge.minAngle
                maximumValueAngle: backend.aoaGauge.maxAngle
            }

            valStr: backend.aoaStr

        }

        CustomGauge {
            id: aos
            myName: "AoS"
            value: backend.aoaValue

            minVal: backend.aosGauge.minValue
            maxVal: backend.aosGauge.maxValue

            customStyle: CircularGaugeStyle {
                minimumValueAngle: backend.aosGauge.minAngle
                maximumValueAngle: backend.aosGauge.maxAngle
            }

            valStr: backend.aosStr

        }
    }
}
