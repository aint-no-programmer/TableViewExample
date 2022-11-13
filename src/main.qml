import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

import QtQuick.Layouts 1.12

import TableModel 1.0

import QtCharts 2.0

import QtQuick.Dialogs 1.3

ApplicationWindow {
    width: 700
    height: 700
    visible: true
    minimumWidth: 650
    minimumHeight: 650
    title: qsTr("QML table view example")
    onWidthChanged: tableView.forceLayout();
    //=============================================
    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("Open file")
                onTriggered: fileFolder.fileDialog.open()
                enabled: qmlAdapter.chooseMeControlEnabled
            }
            Action {
                text: qsTr("&Open folder")
                onTriggered: fileFolder.folderDialog.open()
                enabled: qmlAdapter.chooseMeControlEnabled
            }
            Action { text: qsTr("&Run"); enabled: false;}
            MenuSeparator { }
            Action { text: qsTr("&Quit"); onTriggered: Qt.quit(); }
        }
        Menu {
            title: qsTr("&Report")
            Action { text: qsTr("Export &table"); onTriggered: adapter.createPDFThreadSafe("Report.pdf") }
            Action { text: qsTr("Export chart"); enabled: false; }
            Action { text: qsTr("Ex&port image"); enabled: false; }
        }
        Menu {
            title: qsTr("&Settings")
            Action { text: qsTr("&Decision"); enabled: false; }
            Action { text: qsTr("Reference"); enabled: false; }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("Help"); enabled: false; }
            Action { text: qsTr("&About"); onTriggered: messageDialog.open()}
        }
        MessageDialog {
            id: messageDialog
            title: "About"
            text: "QML table view example."
        }
    }
    //==============================================
    ColumnLayout{
        id: mainLayout
        anchors.fill: parent
        spacing: 10
        /*----------------------------------------*/
        GroupBox{
            Layout.margins: 10
            title: "Choose file/folder"
            font.bold: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: mainLayout.height * 0.3
            ColumnLayout{
                width: parent.width
                height: parent.height
                ChooseMeControl{
                    id: fileFolder
                    enabled: qmlAdapter.chooseMeControlEnabled
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    labelText: "File: "
                    label1Text: "Folder: "
                    buttonText: "Browse"
                    button1Text: "Browse"
                }
                RowLayout{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    spacing: 5
                    Button{
                        enabled: qmlAdapter.chooseMeControlEnabled
                        text: "Color ID"
                        font.bold: true
                        Layout.fillWidth: true
                        onClicked: adapter.processColorIDThreadSafe(fileFolder.fileName)
                        ToolTip.visible: hovered
                        ToolTip.delay: 1000
                        ToolTip.text: "Calculate prediction"
                    }
                    Button{
                        enabled: qmlAdapter.chooseMeControlEnabled
                        text: "Color ID Folder"
                        font.bold: true
                        Layout.fillWidth: true
                        onClicked: adapter.processColorIDFolderThreadSafe(fileFolder.folderName)
                        ToolTip.visible: hovered
                        ToolTip.delay: 1000
                        ToolTip.text: "Calculate prediction for folder"
                    }
                }
            }
        }
        /*----------------------------------------*/
        GroupBox{
            Layout.margins: 10
            title: "Report"
            font.bold: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: mainLayout.height * 0.7
            TableView {
                id: tableView
                anchors.fill: parent
                columnSpacing: 0
                rowSpacing: 0
                clip: true
                topMargin: 50

                ScrollBar.horizontal: ScrollBar {}
                ScrollBar.vertical: ScrollBar {}

                model: tableModel

                Row{
                    y: tableView.contentY
                    z: 2
                    spacing: 0
                    Repeater{
                        model: tableView.columns                        
                        Label{
                            width: index == 0? tableView.width *0.2 : index == 4? tableView.width *0.5 : tableView.width *0.1
//                            width: tableView.width / 5//tableView.columnWidthProvider(modelData)
                            height: 50
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: tableModel.headerData(modelData, Qt.Horizontal)
                            font.bold: true
                            background: Rectangle {color: "#bbbbbb"; border.width: 1}
                        }
                    }
                }

                delegate: Rectangle {
                    /*ToolTip*/
                    ToolTip.visible: mouse.containsMouse
                    ToolTip.delay:1000
                    ToolTip.text: display

                    color: row%2 == 0? "white" : "#dddddd"
//                    implicitWidth: tableView.width / 5
                    implicitWidth: column == 0? tableView.width *0.2 : column == 4? tableView.width *0.5 : tableView.width *0.1
                    implicitHeight: 50
                    border.width: 1

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 5
                        text: display
                        horizontalAlignment: column == 4? Text.AlignLeft : Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    MouseArea {
                        id: mouse
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            console.log("test: " + row + column + index + display)
                        }
                        onDoubleClicked: {
                            console.log("DoubleClick: " + row);                            
                            chartWindow.chartName = tableModel.data(tableModel.index(row, 0));
                            chartWindow.llr = tableModel.data(tableModel.index(row, 2));                            
                            chartWindow.update()
                            chartWindow.visible = true
                        }
                    }
                }
            }
            ApplicationWindow{
                property string chartName
                property double llr
                id: chartWindow             
                Layout.margins: 10
                title: qsTr("Charts")
                width: 400
                height: 400
                minimumWidth: 350
                minimumHeight: 350
                function gauss(a, b, x)
                {
                    var exp = 2.71;
                    return 1/(1+Math.exp((x+0.9996517)*a+b))
                }
                function g2(a,b,x)
                {
                    return Math.abs(a)*Math.exp(a*x+b)/(1+Math.exp(a*x+b))/(1+Math.exp(a*x+b))
                }
                ChartView {
                    legend.visible: false
                    id: chartView
                    title: chartWindow.chartName
                    anchors.fill: parent
                    antialiasing: true

                    SplineSeries {
                        id: spline1
                        //name: chartWindow.llr
                    }
                    SplineSeries {
                        id: spline2
                      //  name: "Some name #2"
                    }
                    SplineSeries {
                        id: spline3
                        name: chartWindow.llr
                    }

                    Component.onCompleted:
                    {
                        console.log("Component.onCompleted: ");
                        for (var x = -1; x < 10; x += 0.01)
                        {
                            spline1.append(x, chartWindow.gauss(-85.19362068,87.12693924,(x)))
                            spline2.append(x, chartWindow.gauss(90.14401299,-87.76264842,(x)))

                        }
                        for (var i=0;i<100;i++)
                        {
                            spline3.append(6, i/100)

                        }

                        chartView.axisX().min = -1;
                        chartView.axisX().max = 7;
                    }
                }
            }

        }
    }
    //==============================================
}
