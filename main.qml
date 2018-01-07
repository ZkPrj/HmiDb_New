import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0

ApplicationWindow {
    id: root
    visible: true
    width: 1000
    height: 800
    title: qsTr("场景数据")

    header: ToolBar{
        Material.foreground: "white"
        RowLayout{
            spacing: 20
            anchors.fill: parent

            Label{
                id: titleLabel
                text: "飞行场景数据库"
                font.pixelSize: 30
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton{
                id: settingBtn
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image/menu.png"

                }
                visible: !initPage.visible
                onClicked: searchPagePopUp.open()
            }
        }
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: SearchPage{
            id: initPage
            width: Math.max(root.width*2/4, 600)
            height: Math.max(root.height*2/4, 450)
            anchors.centerIn: parent
            onSubSearch: {
                stackView.replace(dbComponet)
            }
        }
    }

    Popup{
        id: searchPagePopUp
        x: (root.width - width)/2
        y: (root.height - height)/2
        width: Math.max(root.width*2/4, 600)
        height: Math.max(root.height*2/4, 450)
        modal: true
        focus: true
        contentItem: SearchPage{
            anchors.fill: parent
            onSubSearch: {
                searchPagePopUp.close()
            }
        }
    }
    Component{
        id: dbComponet
        HmiDbView{
            id: hmiDbView
            anchors.fill: parent
        }
    }
}
