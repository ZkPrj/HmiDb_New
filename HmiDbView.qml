import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Rectangle{
    id: root
    width: 1000
    height: 800
    color: "white"


    TableView{
        id: tableView
        sortIndicatorVisible: true
        anchors.fill: parent

        headerDelegate: Rectangle {
            id: headerRect
            height: textItem.implicitHeight * 2
            width: textItem.implicitWidth
            color: "lightsteelblue"
            Text {
                id: textItem
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.leftMargin: 12
                text: styleData.value
                font.bold: true
                font.pixelSize: 15
                elide: Text.ElideRight
                color: "black"
                renderType: Text.NativeRendering
            }
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.topMargin: 1
                width: 2
                color: "#ccc"
            }
        }

        rowDelegate: Rectangle{
            id: rowRect
            height: 30
            border.width: 1
            border.color: "#ccc"
            color: styleData.row%2==0?"white":"lightgray"
        }

        itemDelegate: Rectangle{
            id: itemRect
            border.width: 1
            border.color: "#ccc"
            color: "transparent"
            Text {
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.leftMargin: 12
                text: styleData.value
                font.pixelSize: 13
                elide: Text.ElideRight
                color: "black"
                renderType: Text.NativeRendering
            }
            MouseArea{
                hoverEnabled: true
                anchors.fill: parent
                onDoubleClicked: {
                    core.openSpeFile(styleData.row, styleData.column)
                }
                onEntered: {
                    itemRect.color = "lightgreen"
                }
                onExited: {
                    itemRect.color = "transparent"
                }
            }

        }

        TableViewColumn{
            id: sceneName
            title: "场景名称"
            role: "sceneName"
            horizontalAlignment: Text.AlignHCenter
            width: 100
        }
        TableViewColumn{
            id: sceneAbs
            title: "场景简介"
            role: "sceneAbs"
            width: Math.max(tableView.width*0.4 - 100, tableView.width*0.2)
        }
        TableViewColumn{
            id: sceneReq
            title: "场景需求"
            role: "sceneReq"
            width: tableView.width*0.2
        }
        TableViewColumn{
            id: sceneFlow
            title: "场景流程"
            role: "sceneFlow"
            width: tableView.width*0.2
        }
        TableViewColumn{
            id: sceneResult
            title: "蒙特卡洛仿真"
            role: "sceneResult"
            width: tableView.width*0.2
        }
        model: core



    }



}
