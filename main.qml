import QtQuick 2.2
import QtQuick.Controls 1.1

import "js/game.js" as Game

import cu.uci.fac5.PcVsPC 1.0
import cu.uci.fac5.PersonVsPC 1.0

ApplicationWindow {
    visible: true
    //visibility: "FullScreen"
    visibility: "Maximized"
    width: 1360
    height: 768
    title: qsTr("AIr Craft")

    PcVsPc {
        id: pcsGame
    }

    PersonVsPc {
        id: humanGame
        property string humanName: ""
    }

    Rectangle {
        id: root
        anchors.fill: parent

        Rectangle {
            id: menuContainer
            color: "lightblue"
            width: 300
            anchors.top: root.top
            anchors.bottom: root.bottom

            Rectangle {
                id: newGameBtn
                x: 25
                y: 25
                width: 225
                height: 75
                border.color: "black"
                color: "white"
                radius: 8
                Text {
                    text: qsTr("New Game")
                    font.pointSize: 24
                    anchors.horizontalCenter: newGameBtn.horizontalCenter
                    anchors.verticalCenter: newGameBtn.verticalCenter
                }
                MouseArea {
                    anchors.fill: newGameBtn
                    onClicked: {
                        root.enabled = false
                        newGameContainer.visible = true
                        newGameContainer.enabled = true
                    }
                }
            }

            Rectangle {
                id: playersNameBox
                anchors.top: newGameBtn.bottom
                anchors.margins: 25
                x: 25
                width: 225
                height: 300
                border.color: "black"
                radius: 8
                color: "white"

                Text {
                    x: 10
                    y: 10
                    id: player1Name
                    text: qsTr("")
                    font.pointSize: 24
                }

                Text {
                    x: 10
                    id: player2Name
                    text: qsTr("")
                    font.pointSize: 24
                    anchors.top: player1Name.bottom
                    anchors.margins: 10
                }
            }

            Rectangle {
                id: speedBox
                anchors.top: playersNameBox.bottom
                anchors.margins: 25
                x: 25
                width: 225
                height: 150
                border.color: "black"
                radius: 8

                color: "white"

                Text {
                    id: speedBoxTXT
                    x: 10
                    y: 10
                    text: qsTr("")
                    font.pointSize: 24
                }
            }

            Rectangle {
                id: exitBtn
                anchors.top: speedBox.bottom
                anchors.margins: 25
                x: 25
                width: 225
                height: 100
                border.color: "black"
                radius: 8
                color: "white"

                Text {
                    text: qsTr("Exit")
                    font.pointSize: 24
                    anchors.horizontalCenter: exitBtn.horizontalCenter
                    anchors.verticalCenter: exitBtn.verticalCenter
                }
                MouseArea {
                    anchors.fill: exitBtn
                    onClicked: {
                        Qt.quit()
                    }
                }
            }

        }

        Rectangle {
            id: boardContainer
            width: 768
            anchors.left: menuContainer.right
            anchors.top: root.top
            anchors.bottom: root.bottom

            Image {
                id: board
                source: "img/board.jpg"
                height: 768
                width: 768
            }

            MouseArea {
                id: boardMouseArea
                anchors.fill: boardContainer
                onClicked: {
                    Game.handleClick(mouseX, mouseY);
                }
            }
        }

        Rectangle {
            id: rightContainer
            color: "lightgreen"
            anchors.left: boardContainer.right
            anchors.top: root.top
            anchors.right: root.right
            anchors.bottom: root.bottom
        }
    }

    Rectangle {
        id: newGameContainer
        anchors.fill: parent
        visible: false
        enabled: false
        color: "#CC000000"

        Rectangle {
            id: personVsPcButton
            x: 515
            y: 250
            width: 330
            height: 100
            radius: 8

            Text {
                text: qsTr("Person VS Computer")
                font.pointSize: 24
                anchors.horizontalCenter: personVsPcButton.horizontalCenter
                anchors.verticalCenter: personVsPcButton.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    personVsPcButton.enabled = false
                    personVsPcButton.visible = false
                    pcVsPcButton.enabled = false
                    pcVsPcButton.visible = false

                    playerNameContainer.enabled = true
                    playerNameContainer.visible = true
                }
            }
        }

        Rectangle {
            id: pcVsPcButton
            anchors.horizontalCenter: personVsPcButton.horizontalCenter
            anchors.top: personVsPcButton.bottom
            anchors.margins: 25
            width: 350
            height: 100
            radius: 8

            Text {
                text: qsTr("Computer VS Computer")
                font.pointSize: 24
                anchors.horizontalCenter: pcVsPcButton.horizontalCenter
                anchors.verticalCenter: pcVsPcButton.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.enabled = true
                    newGameContainer.visible = false
                    newGameContainer.enabled = false

                    Game.computerVsComputer()
                }
            }
        }

        Rectangle {
            id: playerNameContainer
            visible: false
            enabled: false
            x: 515
            y: 250
            width: 330
            height: 200
            radius: 8
            color: "orange"

            Text {
                id: label1
                text: qsTr("Write your name")
                font.pointSize: 18
                color: "white"
                x: 25
                y: 25
            }

            TextField {
                id: nameEdit
                anchors.top: label1.bottom
                anchors.margins: 10
                font.pointSize: 18
                height: 50
                width: 250
                x: 25
            }

            Rectangle {
                id: okBtn
                anchors.right: playerNameContainer.right
                anchors.top: nameEdit.bottom
                anchors.margins: 20
                radius: 8
                width: 200
                height: 50
                border.color: "black"
                color: "white"

                Text {
                    text: qsTr("Lets Fight!")
                    font.pointSize: 18
                    anchors.horizontalCenter: okBtn.horizontalCenter
                    anchors.verticalCenter: okBtn.verticalCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if( nameEdit.text != "" ) {
                            personVsPcButton.enabled = true
                            personVsPcButton.visible = true
                            pcVsPcButton.enabled = true
                            pcVsPcButton.visible = true

                            playerNameContainer.enabled = false
                            playerNameContainer.visible = false
                            newGameContainer.enabled = false
                            newGameContainer.visible = false
                            root.enabled = true

                            humanGame.humanName = nameEdit.text
                            Game.personVsComputer()
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: endGame
        anchors.fill: parent
        visible: false
        enabled: false
        color: "#CC000000"

        Rectangle {
            id: winnerRctTxt
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 250
            height: 250
            color: "white"
            radius: 8
            border.color: "black"

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                id: winnerTxt
                text: qsTr("")
                color: "darkblue"
                font.pointSize: 24
            }
        }

        Rectangle {
            id: closeEndGameBtn
            anchors.top: winnerRctTxt.bottom
            anchors.right: winnerRctTxt.right
            width: 75
            height: 50
            anchors.margins: 10
            color: "white"
            border.color: "black"
            radius: 8

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Ok")
                color: "black"
                font.pointSize: 18
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    winnerTxt.text = "";
                    endGame.visible = false;
                    endGame.enabled = false;
                    boardMouseArea.enabled = true;
                }
            }
        }
    }
}
