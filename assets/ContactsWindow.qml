import QtQuick.Window   2.0
import QtQuick.Controls 1.0
import QtQuick          2.0

Window {
    id: win1;
    objectName: "mainWindow"
    width: 320;
    height: 240;
    visible: true;
    title: qsTr("EK Chat");

    ListView {
        id: contactList
        objectName: "contactList"
        anchors.fill: parent
        focus: true

        signal triggered (string user)

        highlight: Rectangle { 
            color: "lightsteelblue" 
            radius: 5
            width: parent.width 
        }
        model: ListModel {
            objectName: "model"
            ListElement {
                name: "konrad@EKCHAT.com"
            }
            ListElement {
                name: "emmanuel@EKCHAT.com"
            }
            ListElement {
                name: "geoff"
            }
        }
        delegate: Text {
            text: name
                MouseArea {
                    onDoubleClicked: {
                        contactList.triggered(name);
                        contactList.currentIndex = index;
                    }
                    onClicked: {
                        contactList.currentIndex = index;
                    }
                    anchors.fill: parent
                }
        }
    }
    ComboBox {
        objectName: "userSelect"
        width: parent.width
        anchors.bottom: contactList.bottom

        model: [ "emmanuel@EKCHAT.com", "konrad@EKCHAT.com" ]
    }
}
