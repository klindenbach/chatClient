import QtQuick.Window   2.0
import QtQuick.Controls 1.0
import QtQuick          2.0

Window {
    id: win1;
    objectName: "mainWindow"
    width: 320;
    height: 240;
    visible: true;
    title: "EK Chat";

    ScrollView {
        id: chatScroll
        objectName: "chatScroll"
        height: 210
        width: 320
        Text { 
            id: chatText
            objectName: "chatText"
            width: 320
            text: "HELLO"
        }
    }
    TextInput {
        id: input
        objectName: "input"
        anchors.top: chatScroll.bottom
        width: 260
    }
    Button { 
        objectName: "sendButton"
        text: "Send"
        anchors.left: input.right
        anchors.bottom: win1.bottom
        anchors.top: chatScroll.bottom
    }
}
