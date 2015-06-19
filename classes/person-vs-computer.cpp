#include "person-vs-computer.h"

QString PersonVsComputer::getPersonName() const
{
    return personName;
}

void PersonVsComputer::setPersonName(const QString &value)
{
    personName = value;
}

void PersonVsComputer::init()
{
    for(int col=0; col<BOARD_SIZE; ++col) {
        board[col][0] = 'B';
        board[col][7] = 'W';
    }

    for(int row=1; row<BOARD_SIZE-1; ++row)
        for(int col=0; col<BOARD_SIZE; col++)
            board[col][row] = '-';
}

QString PersonVsComputer::player1Name()
{
    return player1->getName();
}

QString PersonVsComputer::nextMovePlayer1()
{
    QString move = player1->getMove(board, 'W', 2);
    if( !movementInRule(move, 'W') ) {
        return "";
    }
    else {
        int origX=move[0].digitValue(), origY=move[1].digitValue(),
                destX=move[2].digitValue(), destY=move[3].digitValue();

        board[destX][destY] = board[origX][origY];
        board[origX][origY] = '-';

        return move;
    }
}

QString PersonVsComputer::getGameResult()
{
    return this->gameResult;
}

bool PersonVsComputer::movePiece(QString move)
{
    if( movementInRule(move, 'B') ) {

        // Move piece
        int origX=move[0].digitValue(), origY=move[1].digitValue(),
                destX=move[2].digitValue(), destY=move[3].digitValue();

        board[destX][destY] = board[origX][origY];
        board[origX][origY] = '-';

        return true;
    }

    return false;
}

bool PersonVsComputer::wonPlayer(const QString param_piece)
{
    QChar piece = param_piece[0];
    int enemyPieces = 0, myPieces = 0;
    for(int i=0; i<BOARD_SIZE; ++i)
        for(int j=0; j<BOARD_SIZE; j++) {
            if( board[i][j] != piece && board[i][j] != '-' )
                enemyPieces++;
            else
                myPieces++;
        }
    if( enemyPieces < 3) return true;

    if(myPieces >= 5) {
        for(int row=0; row<BOARD_SIZE-2; row++) {
            for(int col=2; col<BOARD_SIZE-2; col++) {
                if(board[col][row] == piece) {
                    // V pa abajo
                    try {
                        if( board[col+1][row+1]==piece && board[col+2][row+2]==piece &&
                                board[col-1][row+1]==piece && board[col-2][row+2]==piece )
                            return true;
                        // V pa arriba
                        if( board[col+1][row-1]==piece && board[col+2][row-2]==piece &&
                                board[col-1][row-1]==piece && board[col-2][row-2]==piece )
                            return true;
                    } catch(...) {}
                }
            }
        }
    } else {
        for(int row=0; row<BOARD_SIZE-1; row++) {
            for(int col=1; col<BOARD_SIZE-1; col++) {
                if(board[col][row] == piece) {
                    try {
                        // V pa arriba
                        if( board[col+1][row+1]==piece && board[col-1][row+1]==piece )
                            return true;
                        // V pa abajo
                        if( board[col+1][row-1]==piece && board[col-1][row-1]==piece )
                            return true;
                    } catch(...) {}
                }
            }
        }
    }

    return false;
}

bool PersonVsComputer::movementInRule(const QString move, const QChar piece)
{
    int origX = move[0].digitValue(), origY = move[1].digitValue(),
            destX = move[2].digitValue(), destY = move[3].digitValue();

    if(board[origX][origY] != piece) return false;

    // No piece overriding
    if(board[destX][destY] != '-') return false;

    // Same Column or Row
    if(origX != destX && origY != destY) return false;

    // No move between 2 enemies
    // Find the position of the next enemys to the left and right
    int idxL, idxR, idyDwn, idyUp;
    int col = destX, row = destY;
    idxL=col-1;
    while( idxL>=0 && (board[idxL][row]==piece || board[idxL][row]=='-') ) {
        if( board[idxL][row] == piece) idxL = -1;
        else idxL--;
    }
    idxR=col+1;
    while( idxL>=0 && idxR<BOARD_SIZE && (board[idxR][row]==piece || board[idxR][row]=='-') ) {
        if( board[idxR][row] == piece) idxR = BOARD_SIZE;
        else idxR++;
    }
    if( idxL>=0 && idxR<BOARD_SIZE) { // then eat
        return false;
    }
    else
    {
        idyDwn=row-1;
        while( idyDwn>=0 && (board[col][idyDwn]==piece || board[col][idyDwn]=='-') ) {
            if( board[col][idyDwn] == piece) idyDwn = -1;
            else idyDwn--;
        }
        idyUp=row+1;
        while( idyDwn>=0 && idyUp<BOARD_SIZE && (board[col][idyUp]==piece || board[col][idyUp]=='-') ) {
            if(board[col][idyUp] == piece) idyUp = BOARD_SIZE;
            else idyUp++;
        }
        if( idyDwn>=0 && idyUp<BOARD_SIZE) { // then eat
            return false;
        }
    }

    return true;
}

bool PersonVsComputer::draw()
{
    int player1Pieces = 0, player2Pieces = 0;
    for(int i=0; i<BOARD_SIZE; ++i) {
        for(int j=0; j<BOARD_SIZE; ++j) {
            if( board[i][j] == 'W' ) player1Pieces++;
            else if( board[i][j] == 'B' ) player2Pieces++;
        }
    }

    if( player1Pieces < 3 && player2Pieces < 3)
        return true;
    else
        return false;
}

QString PersonVsComputer::tryEat(int player)
{
    QChar piece;
    QString result = "";
    // if player = 1 try to eat Black piece and viceversa.
    // remember that B's plays first.
    if(player == 2) piece = 'B';
    else piece = 'W';

    int idxL, idxR, idyDwn, idyUp;
    for(int col=0; col<BOARD_SIZE; col++)
        for(int row=0; row<BOARD_SIZE; row++)
            if( board[col][row] == piece ) {
                // Find the position of the next enemys to the left and right
                idxL=col-1;
                while( idxL>=0 && (board[idxL][row]==piece || board[idxL][row]=='-') ) {
                    if( board[idxL][row] == piece) idxL = -1;
                    else idxL--;
                }
                idxR=col+1;
                while( idxL>=0 && idxR<BOARD_SIZE && (board[idxR][row]==piece || board[idxR][row]=='-') ) {
                    if( board[idxR][row] == piece) idxR = BOARD_SIZE;
                    else idxR++;
                }
                if( idxL>=0 && idxR<BOARD_SIZE) { // then eat
                    result += QString::number(col)+QString::number(row);
                    board[col][row] = '-';
                }
                else
                {
                    idyDwn=row-1;
                    while( idyDwn>=0 && (board[col][idyDwn]==piece || board[col][idyDwn]=='-') ) {
                        if( board[col][idyDwn] == piece) idyDwn = -1;
                        else idyDwn--;
                    }
                    idyUp=row+1;
                    while( idyDwn>=0 && idyUp<BOARD_SIZE && (board[col][idyUp]==piece || board[col][idyUp]=='-') ) {
                        if(board[col][idyUp] == piece) idyUp = BOARD_SIZE;
                        else idyUp++;
                    }
                    if( idyDwn>=0 && idyUp<BOARD_SIZE) { // then eat
                        result += QString::number(col)+QString::number(row);
                        board[col][row] = '-';
                    }
                }
            }

    return result;
}

PersonVsComputer::PersonVsComputer()
{
    player1 = new Player1();
    gameResult = "";
}
