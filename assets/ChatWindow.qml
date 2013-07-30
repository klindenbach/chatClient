import QtQuick.Window 2.0
import QtQuick        2.0

Window {
    id: win1;
    objectName: "mainWindow"
    width: 320;
    height: 240;
    visible: true;
    title: "EK Chat";

    Text { 
        id: chatText
        objectName: "chatText"
        width: 320
        height: 210
        text: "HELLO"
    }
    Button { 
        objectName: "sendButton"
        text: "Send"
        anchors.bottom: win1.bottom
        anchors.top: chatText.bottom
    }
}
