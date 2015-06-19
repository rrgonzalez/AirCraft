import QtQuick 2.0

Item {
    id: plane
    height: 96
    width: 96
    property string side: "-"
    property int col: 0
    property int row: 0
    property bool selected: false
    onColChanged: {
        x = col*96// +3
    }
    onRowChanged: {
        y = row*96// +3
    }

    Image {
        anchors.fill: parent
        source: {
            if( side == 'W' ) {
                if( selected )
                    return "img/selected-plane.png";
                else
                    return "img/plane-short.png";
            } else {
                if( selected )
                    return "img/selected-plane.png";
                else
                    return "img/plane-short2.png";
            }
        }
    }
}
