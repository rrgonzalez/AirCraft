var piecesAmount = 8;
var board = new Array(64);
var Plane;
var activePiece = null;

// 0 <= coor < 8
function index(col, row) {
    return col + row*8;
}

function cleanBoard() {
    if( activePiece != null )
        activePiece.destroy();

    // Clean garbage
    for(var i=0; i<64; i++) {
        if( board[i] != null)
            board[i].destroy();
    }

    if (Plane == null)
        Plane = Qt.createComponent("../Plane.qml");

    for(var i=0; i<piecesAmount; i++) {
        if (Plane.status == Component.Ready) {
            var newPlane = Plane.createObject(boardContainer, {"col": i,"row": 7, "side":"W" } );
            board[index(i, 7)] = newPlane;
        }

        if (Plane.status == Component.Ready) {
            var newPlane = Plane.createObject(boardContainer, {"col": i,"row": 0, "side":"B" } );
            board[index(i, 0)] = newPlane;
        }
    }
}

function computerVsComputer() {
    cleanBoard();

    pcsGame.init();

    // load Names
    player1Name.text = pcsGame.player1Name();
    player2Name.text = pcsGame.player2Name();

    // Simulate
    //    pcsGame.simulateGame();
    // load Plays
    //   var plays = pcsGame.playsList();

    //    player2Name.text = plays.length

    // show Play with Timer
}

function personVsComputer() {
    cleanBoard();

    humanGame.init();

    player1Name.text = humanGame.humanName;
    player2Name.text = humanGame.player1Name();

    speedBoxTXT.text = "Speed controls"
}

function playPC() {
    boardMouseArea.enabled = false;

    var move = humanGame.nextMovePlayer1();

    // Process Eating
    var eatPieces = humanGame.tryEat(2);
    eatPieces += humanGame.tryEat(1);
    var aux;
    var x, y;
    for(var i=0; i<eatPieces.length; i+=2) {
        x = parseInt( eatPieces[i] );
        y = parseInt( eatPieces[i+1] );
        aux = board[ index(x, y) ];
        board[ index(x, y) ] = null;
        aux.destroy();
    }

    if( humanGame.wonPlayer('W') ) {
        boardMouseArea.enabled = false;
        endGame.visible = true;
        endGame.enabled = true;
        winnerTxt.text = "Winner " + player2Name.text;
        //console.log( "Winner " + player2Name.text );
        return ;
    }

    if( move == "" ) {
        // There was an error with the move
        return ;
    }

    var origX = parseInt(move[0]), origY = parseInt(move[1]),
            destX = parseInt(move[2]), destY = parseInt(move[3]);

    //console.log( move );

    selectPiece(origX, origY);
    movePiece(destX, destY);

    boardMouseArea.enabled = true;
}

function handleClick(xPos, yPos) {

    var col = Math.floor( xPos/96 );
    var row = Math.floor( yPos/96 );
    //console.log( "col "+ col + " row " + row );

    if( activePiece == null && board[ index(col, row) ] != null && board[ index(col, row) ].side == 'B') {
        selectPiece(col, row);
        //console.log(" select with active piece null ");
    }
    else {
        if( board[ index(col, row) ] == null) {
            var move = "";
            move += activePiece.col;
            move += activePiece.row;
            move += col; move += row;
            if( humanGame.movePiece(move) ) {
                movePiece(col, row);

                // Process eating
                var eatPieces = humanGame.tryEat(1);
                eatPieces += humanGame.tryEat(2);
                var aux;
                var x, y;
                for(var i=0; i<eatPieces.length; i+=2) {
                    x = parseInt( eatPieces[i] );
                    y = parseInt( eatPieces[i+1] );
                    aux = board[ index(x, y) ];
                    board[ index(x, y) ] = null;
                    aux.destroy();
                }

                if(  humanGame.wonPlayer('B') ) {
                    boardMouseArea.enabled = false;
                    endGame.visible = true;
                    endGame.enabled = true;
                    winnerTxt.text = "Winner " + player1Name.text;
                    //console.log( "Winner " + player1Name.text );
                } else {
                    playPC();
                }


            } else {
                //console.log( "big problem" );
            }
        }
        else if(board[ index(col, row) ].side == 'B') {// select other piece
            selectPiece(col, row);
            //console.log( "select other piece" );
        }
    }
}

function selectPiece(col, row) {
    if( board[ index(col, row) ] == null ) return ;

    if( activePiece == null ) {
        //console.log( col + " " + row );
        activePiece = board[ index(col, row) ];
        activePiece.selected = true;
        board[ index(col, row) ] = null;
    } else {
        var auxc = activePiece.col;
        var auxr = activePiece.row;
        activePiece.selected = false;
        board[ index(auxc, auxr) ] = activePiece;
        activePiece = board[ index(col, row) ];
        activePiece.selected = true;
    }
}

function movePiece(col, row) {
    if( activePiece == null ) return ;

    activePiece.col = col;
    activePiece.row = row;
    board[ index(col, row) ] = activePiece;
    activePiece.selected = false;
    activePiece = null;
}
