import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.labs.platform 1.1 as Labs
import parser 1.0
import utility_plugin 1.0

ApplicationWindow {
    id: root
    visible: true
    width: AppSettings.value("MainWindow/width", 640)
    height: AppSettings.value("MainWindow/height", 480)
    x: AppSettings.value("MainWindow/x", 640)
    y: AppSettings.value("MainWindow/y", 640)
    title: qsTr("SVG Creator")

    Component.onDestruction: {
        AppSettings.setValue("MainWindow/width", root.width)
        AppSettings.setValue("MainWindow/height", root.height)
        AppSettings.setValue("MainWindow/x", root.x)
        AppSettings.setValue("MainWindow/y", root.y)
        Recoder.saveSettings()
    }

    property bool parserMode: false

    menuBar: MenuBar {
        id: header
        opacity: 0.2
        Menu {
            title: qsTr("Файл")
            Action {
                id: chooseGenFolder;
                text: qsTr("Генерировать код для GraphViz");
                onTriggered: {
                    folderDialog.open()
                }
            }
            Action {
                id: chooseParseFolder;
                text: qsTr("Парсить SVG файл");
                onTriggered: {
                    folderDialog.open()
                    folderDialog.currentFolder = AppSettings.value("Parser/location" ,Labs.StandardPaths.writableLocation(Labs.StandardPaths.HomeLocation))
                }
            }
            MenuSeparator {}
            Action { id: quit; text: qsTr("Выход"); onTriggered: root.close() }
        }
    }

    SwipeView {
        id: parser
        anchors.fill: parent
        opacity: 0.2

        Page {
            id: recoder

            Button {
                id: record
                text: qsTr("Запись в файл")
                height: 30
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                onClicked: Recoder.record()
            }

            Button {
                id: parse
                text: qsTr("Создать объекты")
                height: 30
                anchors.bottom: parent.bottom
                anchors.left: record.right
                anchors.leftMargin: 5
                onClicked: Recoder.parse()
            }
        }

        Page {
            id: xml

        }
    }

    ColumnLayout {
        id: mainButtons

        anchors.centerIn: parent
        width: 400
        spacing: 5

        onOpacityChanged: if(opacity == 0) visible = false

        Button {
            id: generator
            text: qsTr("Генерировать код для GraphViz")
            implicitHeight: 100
            Layout.fillWidth: true
            onPressed: {
                parserMode = true
                opacityAnim.running = true
                mainAnim.running = true
            }
        }

        Button {
            id: parserButton
            text: qsTr("Создать JS массив из SVG")
            implicitHeight: 100
            Layout.fillWidth: true
            onPressed: {
                parserMode = false
                opacityAnim.running = true
                mainAnim.running = true
            }
        }

        NumberAnimation {
            id: opacityAnim
            target: mainButtons
            property: "opacity"
            from: opacity
            to: 0
            duration: 500
        }
    }


    footer: ListView {
        id: footer
        clip: true
        height: 100
        width: parent.width
        model: Recoder.info
        delegate: Text {
            text: modelData
        }
    }

    Connections {
        target: Recoder
        onInfoChanged: footer.positionViewAtEnd()
    }

    NumberAnimation {
        id: mainAnim
        targets: [header, footer, parser]
        properties: "opacity"
        from: header.opacity
        to: 1
        duration: 500
    }

    Labs.FolderDialog {
        id: folderDialog
        onFolderChanged: Recoder.location = folder
        onCurrentFolderChanged: console.log("current folder", currentFolder)
    }
}
