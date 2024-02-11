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
            value: backend.aoaValue

            minimumValue: backend.aoaGauge.minValue
            maximumValue: backend.aoaGauge.maxValue

            style: CircularGaugeStyle {
                minimumValueAngle: backend.aoaGauge.minAngle
                maximumValueAngle: backend.aoaGauge.maxAngle
            }


        }

        CustomGauge {
            id: aos
            value: backend.aoaValue

            minimumValue: backend.aosGauge.minValue
            maximumValue: backend.aosGauge.maxValue

            style: CircularGaugeStyle {
                minimumValueAngle: backend.aosGauge.minAngle
                maximumValueAngle: backend.aosGauge.maxAngle
            }

        }
    }
}
