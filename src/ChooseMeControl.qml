import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.0

Item {
    property alias fileDialog: fileDialog
    property alias folderDialog: folderDialog

    property string labelText
    property string label1Text
    property string buttonText
    property string button1Text
    property alias fileName: textField.text
    property alias folderName: textField1.text
    Rectangle {
        id: rectangle
        color: "#cccccc"
        anchors.fill: parent
        GridLayout {
            id: grid
            anchors.fill: parent
            anchors.margins: 5
            columns: 3
            rowSpacing: 5
            columnSpacing: 5
            Label {
                id: label
                text: labelText
                padding: 10
                horizontalAlignment: Text.AlignHCenter
            }

            TextField {
                id: textField
                Layout.fillWidth: maximumWidth
                text: qmlAdapter.fileName//fileDialog.fileUrl
                onEditingFinished: qmlAdapter.fileName = text
                onAccepted: qmlAdapter.fileName = text
            }

            Button {
                id: button
                text: buttonText
                onClicked: fileDialog.open()
            }

            Label {
                id: label1
                text: label1Text
                horizontalAlignment: Text.AlignHCenter
                padding: 10
            }

            TextField {
                id: textField1
                Layout.fillWidth: maximumWidth
                text: qmlAdapter.folderName//folderDialog.folder
                onEditingFinished: qmlAdapter.folderName = text
                onAccepted: qmlAdapter.folderName = text
            }

            Button {
                id: button1
                text: button1Text
                onClicked: {
                    console.log(qmlAdapter.folderNameUrl)
                    folderDialog.open()
                }
            }
        }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: qmlAdapter.fileNameUrl
        onAccepted: {
            qmlAdapter.fileName = fileDialog.fileUrl
            qmlAdapter.fileNameUrl = fileDialog.fileUrl
            console.log("You choose file: " + fileDialog.fileUrl)
        }
        onRejected: {
        }
    }
    FileDialog {
        id: folderDialog
        title: "Please choose a folder"
        folder: qmlAdapter.folderNameUrl
        selectFolder: true
        onAccepted: {
            qmlAdapter.folderName = folderDialog.folder
            qmlAdapter.folderNameUrl = folderDialog.folder
            console.log("You choose folder: " + folderDialog.folder)
        }
        onRejected: {
        }
    }
}
