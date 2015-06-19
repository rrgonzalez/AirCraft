#include "player2.h"

bool Player2::wonPlayer(const QChar piece)
{
    int enemyPieces = 0, myPieces = 0;
    for(int i=0; i<BOARD_SIZE; ++i)
        for(int j=0; j<BOARD_SIZE; j++) {
            if( myBoard[i][j] != piece && myBoard[i][j] != '-' )
                enemyPieces++;
            else
                myPieces++;
        }
    if( enemyPieces < 3) return true;

    if(myPieces >= 5) {
        for(int col=2; col<BOARD_SIZE-2; col++) {
            for(int row=2; row<BOARD_SIZE-2; row++) {
                if(myBoard[col][row] == piece) {
                    // V pa arriba
                    if( myBoard[col+1][row+1]==piece && myBoard[col+2][row+2]==piece &&
                        myBoard[col-1][row+1]==piece && myBoard[col-2][row+2]==piece )
                        return true;
                    // V pa abajo
                    if( myBoard[col+1][row-1]==piece && myBoard[col+2][row-2]==piece &&
                            myBoard[col-1][row-1]==piece && myBoard[col-2][row-2]==piece )
                        return true;
                }
            }
        }
    } else {
        for(int col=1; col<BOARD_SIZE-1; col++) {
            for(int row=1; row<BOARD_SIZE-1; row++) {
                if(myBoard[col][row] == piece) {
                    // V pa arriba
                    if( myBoard[col+1][row+1]==piece && myBoard[col-1][row+1]==piece )
                        return true;
                    // V pa abajo
                    if( myBoard[col+1][row-1]==piece && myBoard[col-1][row-1]==piece )
                        return true;
                }
            }
        }
    }

    return false;
}

bool Player2::movementInRule(const QString move, const QChar piece)
{
    int origX = move[0].digitValue(), origY = move[1].digitValue(),
            destX = move[2].digitValue(), destY = move[3].digitValue();

    if(myBoard[origX][origY] != piece) return false;

    // No piece overriding
    if(myBoard[destX][destY] != '-') return false;

    // Same Column or Row
    if(origX != destX && origY != destY) return false;

    // No move between 2 enemies
    if( origY == destY ) {
        int down = origY-1;
        int up = origY+1;
        while( down >= 0 && ( myBoard[destX][down] == piece || myBoard[destX][down] == '-')  ) {
            if( myBoard[destX][down] == piece ) down = -1;
            else down--;
        }
        while( up < BOARD_SIZE && ( myBoard[destX][up] == piece || myBoard[destX][up] == '-')  ) {
            if( myBoard[destX][up] == piece ) up = BOARD_SIZE;
            else up++;
        }

        //cout<< "down: " << down << " up: " << up << endl;

        if( down >= 0 && up < BOARD_SIZE ) return false;

    } else {
        int left = origX-1;
        int right = origX+1;
        while( left >= 0 && ( myBoard[left][destY] == piece ||  myBoard[left][destY] == '-')  ) {
            if(  myBoard[left][destY] == piece ) left = -1;
            else left--;
        }
        while( right < BOARD_SIZE && ( myBoard[right][destY] == piece || myBoard[right][destY] == '-')  ) {
            if( myBoard[right][destY] == piece ) right = BOARD_SIZE;
            else right++;
        }

        //cout<< "left: " << left << " right: " << right << endl;

        if( left >= 0 && right < BOARD_SIZE ) return false;
    }

    return true;
}

Player2::Player2()
{
}

QString Player2::getName()
{
    return "Spartan";
}

const QString Player2::getId()
{
    return this->id;
}

void Player2::setId(const QString id)
{
    this->id = id;
}

QString Player2::getMove(const QChar board[BOARD_SIZE][BOARD_SIZE],const QChar piece,const int maxLevel)
{
    // Copy board
    for(int i=0; i<BOARD_SIZE; ++i)
        for(int j=0; j<BOARD_SIZE; ++j)
            myBoard[i][j] = board[i][j];

    qsrand( time(NULL) );
    QString move;
    int destX, destY, origX, origY;

    for(int i=0; i<BOARD_SIZE; ++i) {
        for(int j=0; j<BOARD_SIZE; ++j) {
            if(board[i][j] == piece) {
                origX = i; origY = j;
            }
        }
    }

    destX = origX;
    do {
        destY = qrand()%8;
        move = QString::number(origX)+QString::number(origY)+
               QString::number(destX)+QString::number(destY);
         qDebug("%d %d %d %d %d", origX, origY, destX, destY, movementInRule(move, piece) );
    } while( !movementInRule(move, piece) );

    return move;
}
