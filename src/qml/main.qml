import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultimedia

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property int id: 0

    Connections {
        id: pr
        target: StreamingProvider

        function onImageChanged() {
            image.reload()
        }
    }


    Image {
        id: image
        source: "image://providers/image"

        function reload() {

            image.source ="image://providers/image" + id.toString()
            id++
        }
    }
}
