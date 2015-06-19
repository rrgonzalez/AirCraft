#include "computer-vs-computer.h"

ComputerVsComputer::ComputerVsComputer()
{
    player1 = new Player1();
    player2 = new Player2();
    gameResult = "";
}

bool ComputerVsComputer::wonPlayer(const char piece)
{
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
        for(int col=2; col<BOARD_SIZE-2; col++) {
            for(int row=2; row<BOARD_SIZE-2; row++) {
                if(board[col][row] == piece) {
                    // V pa arriba
                    if( board[col+1][row+1]==piece && board[col+2][row+2]==piece &&
                        board[col-1][row+1]==piece && board[col-2][row+2]==piece )
                        return true;
                    // V pa abajo
                    if( board[col+1][row-1]==piece && board[col+2][row-2]==piece &&
                        board[col-1][row-1]==piece && board[col-2][row-2]==piece )
                        return true;
                }
            }
        }
    } else {
        for(int col=1; col<BOARD_SIZE-1; col++) {
            for(int row=1; row<BOARD_SIZE-1; row++) {
                if(board[col][row] == piece) {
                    // V pa arriba
                    if( board[col+1][row+1]==piece && board[col-1][row+1]==piece )
                        return true;
                    // V pa abajo
                    if( board[col+1][row-1]==piece && board[col-1][row-1]==piece )
                        return true;
                }
            }
        }
    }

    return false;
}

bool ComputerVsComputer::movementInRule(const QString move, const QChar piece)
{
    int origX = move[0].digitValue(), origY = move[1].digitValue(),
            destX = move[2].digitValue(), destY = move[3].digitValue();

    if(board[origX][origY] != piece) return false;

    // No piece overriding
    if(board[destX][destY] != '-') return false;

    // Same Column or Row
    if(origX != destX && origY != destY) return false;

    // No move between 2 enemies
    if( origY == destY ) {
        int down = origY-1;
        int up = origY+1;
        while( down >= 0 && ( board[destX][down] == piece || board[destX][down] == '-')  ) {
            if( board[destX][down] == piece ) down = -1;
            else down--;
        }
        while( up < BOARD_SIZE && ( board[destX][up] == piece || board[destX][up] == '-')  ) {
            if( board[destX][up] == piece ) up = BOARD_SIZE;
            else up++;
        }

        //cout<< "down: " << down << " up: " << up << endl;

        if( down >= 0 && up < BOARD_SIZE ) return false;

    } else {
        int left = origX-1;
        int right = origX+1;
        while( left >= 0 && ( board[left][destY] == piece ||  board[left][destY] == '-')  ) {
            if(  board[left][destY] == piece ) left = -1;
            else left--;
        }
        while( right < BOARD_SIZE && ( board[right][destY] == piece || board[right][destY] == '-')  ) {
            if( board[right][destY] == piece ) right = BOARD_SIZE;
            else right++;
        }

        //cout<< "left: " << left << " right: " << right << endl;

        if( left >= 0 && right < BOARD_SIZE ) return false;
    }

    return true;
}

bool ComputerVsComputer::draw()
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

void ComputerVsComputer::movePiece(QString move)
{
    int origX=move[0].digitValue(), origY=move[1].digitValue(),
            destX=move[2].digitValue(), destY=move[3].digitValue();

    board[destX][destY] = board[origX][origY];
    board[origX][origY] = '-';
}

void ComputerVsComputer::tryEat(int player)
{
    QChar piece;
    // if player = 1 try to eat Black piece and viceversa.
    if(player == 1) piece = 'B';
    else piece = 'W';

    int idxMin, idxMax;

    for(int col=0; col<BOARD_SIZE; ++col) {
        for(int row=0; row<BOARD_SIZE; ++row) {
            if( board[col][row] == piece ) {
                idxMin = col-1; idxMax = col+1;
                while( idxMin>=0 && (board[idxMin][row]=='-' || board[idxMin][row]!=piece) ) {
                    if( board[idxMin][row] == piece ) idxMin = -1;
                    else idxMin--;
                }
                while( idxMax<BOARD_SIZE && (board[idxMax][row]=='-' || board[idxMax][row]!=piece) ) {
                    if( board[idxMax][row] == piece ) idxMax = BOARD_SIZE;
                    else idxMax++;
                }
                if(idxMin>=0 && idxMax<BOARD_SIZE) board[col][row] = '-';

                idxMin = row-1; idxMax = row+1;
                while( idxMin>=0 && (board[col][idxMin]=='-' || board[col][idxMin]!=piece) ) {
                    if( board[col][idxMin] == piece ) idxMin = -1;
                    else idxMin--;
                }
                while( idxMax<BOARD_SIZE && (board[col][idxMax]=='-' || board[col][idxMax]!=piece) ) {
                    if( board[col][idxMax] == piece ) idxMax = BOARD_SIZE;
                    else idxMax++;
                }
                if(idxMin>=0 && idxMax<BOARD_SIZE) board[col][row] = '-';
            }
        }
    }
}

void ComputerVsComputer::init()
{
    for(int col=0; col<BOARD_SIZE; ++col) {
        board[col][0] = 'W';
        board[col][7] = 'B';
    }

    for(int row=1; row<BOARD_SIZE-1; ++row)
       for(int col=0; col<BOARD_SIZE; col++)
            board[col][row] = '-';
}

/*void ComputerVsComputer::simulateGame()
{
    int plays = 0;
    QString move;

    while( plays < 300) {
        move = player1->getMove(board, 'W', 5);
        if( movementInRule(move, 'W') ) {
            m_playsList.append( move );
            movePiece(move);
            tryEat(1);
            if( draw() ) {
                gameResult = "Draw";
                return ;
            } else if( wonPlayer('W') ) {
                gameResult = "Player1Win";
                return ;
            }
        }

        move = player2->getMove(board, 'B', 5);
        if( movementInRule(move, 'B') ) {
            m_playsList.append( move );
            movePiece(move);
            tryEat(2);
            if( draw() ) {
                gameResult = "Draw";
                return ;
            } else if( wonPlayer('B') ) {
                gameResult = "Player2Win";
                return ;
            }
        }

        plays+=2;
    }
}*/

/*QList<QString> ComputerVsComputer::playsList()
{
    QList<QString> lista;
    lista.append("1");
    lista.append("1");
    lista.append("1");
    return lista;
}
*/
QString ComputerVsComputer::player1Name()
{
    return this->player1->getName();
}

QString ComputerVsComputer::player2Name()
{
    return this->player2->getName();
}

QString ComputerVsComputer::nextMovePlayer1()
{
    QString move = player1->getMove(board, 'W', 5);
    if( !movementInRule(move, 'W') )
        return "";
    else {
        movePiece(move);
        tryEat(1);
        if( draw() ) {
            gameResult = "Draw";
            return "";
        } else if( wonPlayer('W') ) {
            gameResult = "Player1Win";
            return "";
        }

        return move;
    }
}

QString ComputerVsComputer::nextMovePlayer2()
{
    QString move = player2->getMove(board, 'B', 5);
    if( !movementInRule(move, 'B') )
        return "";
    else {
        movePiece(move);
        tryEat(1);
        if( draw() ) {
            gameResult = "Draw";
            return "";
        } else if( wonPlayer('B') ) {
            gameResult = "Player2Win";
            return "";
        }

        return move;
    }
}

QString ComputerVsComputer::getGameResult()
{
    return this->gameResult;
}
