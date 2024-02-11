import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0

CircularGauge {
    Layout.fillWidth:true
    Layout.minimumHeight: 100
    Layout.minimumWidth: 100
    Layout.preferredHeight: 350
    Layout.preferredWidth: 450


    Behavior on value {
        NumberAnimation {
            duration: 50
        }
    }
}
