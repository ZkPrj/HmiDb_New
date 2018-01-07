import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: searchPage
    width: 1000
    height: 800
    color: "white"
    border.color: "#0dd74f"
    border.width: 2
    signal subSearch

    Label{
        id:title
        text: qsTr("分类查找")
        font.pixelSize: 14
        font.bold: true
        anchors.left: classSearchRct.left
        anchors.bottom: classSearchRct.top
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
    }

    Rectangle{
        id: fstRow
        y: 50
        //anchors.horizontalCenter: searchPage.horizontalCenter
        x: (parent.width - searchBtn.x - searchBtn.width)/2
        Button{
            id: allOpBtn
            text: qsTr("浏览所有操作")
            font.bold: true
            font.pixelSize: 18
            onClicked: {
                core.getSceneList()
                subSearch();
            }
        }

        TextField{
            id: searchTxtF
            anchors.left: allOpBtn.right
            anchors.leftMargin: 50
            anchors.top: allOpBtn.top
            anchors.topMargin: 0
            anchors.bottom: allOpBtn.bottom
            width: 200
        }

        Button{
            id: searchBtn
            text: qsTr("搜 索")
            font.pixelSize: 16
            font.bold: true
            anchors.left: searchTxtF.right
            anchors.leftMargin: 0
            anchors.top: searchTxtF.top
            anchors.bottom: searchTxtF.bottom
            width: 80
            onClicked: {
                core.getMatchKey(searchTxtF.text.trim())
                subSearch();
            }
        }
    }

    Rectangle{
        id: classSearchRct
        anchors.horizontalCenter: searchPage.horizontalCenter
        width: 400
        anchors.top: fstRow.bottom
        anchors.topMargin: 100
        height: 250
        color: "#f5f5f3"
        border.color: "#edf2ed"

        Column{
            id: column1
           anchors.centerIn: parent
           spacing: 15
           Row{
               id: row1
               anchors.right: parent.right
               anchors.rightMargin: 0
               spacing: 8
               Label{
                   id: planeTypeTxt
                   text: qsTr("机型")
                   font.pixelSize: 14
                   anchors.verticalCenter: parent.verticalCenter
                   //Layout.alignment: Qt.AlignRight
               }
               ComboBox{
                   //Layout.alignment: Qt.AlignRight
                   id: planeTypeCb
                   width: 200
               }
           }

           Row{
               id: row2
               anchors.right: parent.right
               anchors.rightMargin: 0
               spacing: 8
               Label{
                   id: flightPhaseTxt
                   text: qsTr("飞行阶段")
                   font.pixelSize: 14
                   anchors.verticalCenter: parent.verticalCenter
                   //Layout.alignment: Qt.AlignRight
               }
               ComboBox{
                   id: flightPhaseCb
                   width: 200
                   //Layout.alignment: Qt.AlignRight
               }
           }

           Row{
               id: row3
               anchors.right: parent.right
               anchors.rightMargin: 0
               spacing: 8
               Label{
                   id: taskDifTxt
                   text: qsTr("任务难度")
                   font.pixelSize: 14
                   anchors.verticalCenter: parent.verticalCenter
                   //Layout.alignment: Qt.AlignRight
               }
               ComboBox{
                   id: taskDifCb
                   width: 200
                   //Layout.alignment: Qt.AlignRight
               }
           }

           Button{
               id: findBtn
               text: qsTr("查 找")
               font.pixelSize: 16
               width: 150
               font.bold: true
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.horizontalCenterOffset: 20
               onClicked: {
                   core.getClassList(planeTypeCb.currentText, flightPhaseCb.currentText, taskDifCb.currentText)
                   subSearch();
               }
           }
        }

    }
    Component.onCompleted: {
        planeTypeCb.model = core.getPlaneTypes()
        flightPhaseCb.model = core.getFlightPhases()
        taskDifCb.model = core.getTaskDif()
    }


}
