#include "player1.h"

#include <QPair>
#include <vector>
using namespace std;

bool Player1::wonPlayer(const QChar piece)
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

bool Player1::movementInRule(const QString move, const QChar piece)
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

int Player1::heuristic(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece)
{
    const int K_DIF_PIECES = 25000;
    const int K_V5 = 10000000;
    const int K_V4 = 10000;
    const int K_V3 = 100;
    const int K_V2 = 1;

    vector<int> ptsV = cantPosiblesV(board, piece);

    int val = K_DIF_PIECES * ventajaPiezas(board, piece);

    val += K_V5*ptsV[3] + K_V4*ptsV[2] + K_V3*ptsV[1] + K_V2 * ptsV[0];

    val += rand() % 112;

    qDebug( "Val %d", val );
    return val;

    // Team de Anelis y JC

    /*int result=0;

    int valores_j[8];
    for(int j=0;j<8;j++)
    {
        if(j==1 || j==6){
            valores_j[j]=1;
        }
        else
            valores_j[j]=2;
    }

    int valores_i[8];
    for(int i=0;i<8;i++)
    {
        if(i==0 || i==7)
            valores_i[i]=2;
        else if(i==6 || i==1)
            valores_i[i]=3;
        else if(i==5 || i==2)
            valores_i[i]=4;
        else
            valores_i[i]=1;
    }
    //Crear la matriz de ptos con los valores
    //asignados en las filas y las columnas

    int pts[8][8];

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            pts[i][j]=valores_i[i]+valores_j[j];
        }
    }

    //Buscar adyacentes
    int dx[] = {-1, 0, 0, 1};
    int dy[] = {0, -1, 1, 0};

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++) {
            if( board[i][j] == piece ) {

                for(int k=0; k<8; k++) {
                    if( i+dx[k] >= 0 && i+dx[k] < 8 &&
                            j+dy[k] >= 0 && j+dy[k] < 8 ) {
                        pts[ i+dx[k] ][ j+dy[k] ] -= 3;
                    }
                }
            }
            else if( board[i][j] != piece ) {
                for(int k=0; k<8; k++) {
                    if( i+dx[k] >= 0 && i+dx[k] < 8 &&
                            j+dy[k] >= 0 && j+dy[k] < 8 ) {
                        pts[ i+dx[k] ][ j+dy[k] ] += 2;
                    }
                }
            }
        }


    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++) {
            if( board[i][j] == piece ) {
                result+=pts[i][j];
            }

        }

    return result;*/
}

QPair<QString, int> Player1::minimax(const QChar board[BOARD_SIZE][BOARD_SIZE], QChar piece, int level)
{
    if( level != 0 && level != 1) {
        qDebug("level %d -------------------------------------------", level);
    }
    QString lol = "";
    if( wonPlayer(piece) )
        return qMakePair(lol, 99999999);

    if( (piece == 'W' && wonPlayer('B') ) || (piece == 'B' && wonPlayer('W') ) )
        return qMakePair(lol, -99999999);

    if( level==0 )
        return qMakePair(lol, heuristic(board, piece) );


    QString bestMove = "";
    int bestPts = 0;
    if( level & 1 )
        bestPts = INT_MAX;
    else
        bestPts = INT_MIN;

    // Analizar todas las posibles.
    for(int origY=0; origY<BOARD_SIZE; origY++) {
        for(int origX=0; origX<BOARD_SIZE; origX++) {
            if( board[origX][origY] == piece ) {

                // Move in row
                int destX, destY = origY;
                for(destX = 0; destX < BOARD_SIZE; destX++) {
                    if( board[destX][destY] == '-' ) {

                        // copy board
                        QChar myBoard[BOARD_SIZE][BOARD_SIZE];
                        for(int i=0; i<BOARD_SIZE; i++)
                            for(int j=0; j<BOARD_SIZE; j++)
                                myBoard[i][j] = board[i][j];

                        QString candMove = QString::number(origX) + QString::number(origY) +
                                QString::number(destX) + QString::number(destY);
                        QChar candPiece;

                        // Si es posible el mov. generar sus hijos y obtener la heuristica.
                        if( movementInRule(candMove, piece) ) {
                            if( piece == 'W' ) candPiece = 'B';
                            else if( piece == 'B' ) candPiece = 'W';

                            myBoard[destX][destY] = myBoard[origX][origY];
                            myBoard[origX][origY] = '-';

                            int pts = minimax(myBoard, candPiece, level-1).second;

                            if( level & 1 ) {
                                if( pts < bestPts ) {
                                    bestPts = pts;
                                    bestMove = candMove;
                                }
                            }
                            else {
                                if( pts > bestPts ) {
                                    bestPts = pts;
                                    bestMove = candMove;
                                }
                            }
                        }
                    }
                }

                // Move in colum
                destX = origX;
                for(destY = 0; destY < BOARD_SIZE; destY++) {
                    if( board[destX][destY] == '-' ) {

                        // copy board
                        QChar myBoard[BOARD_SIZE][BOARD_SIZE];
                        for(int i=0; i<BOARD_SIZE; i++)
                            for(int j=0; j<BOARD_SIZE; j++)
                                myBoard[i][j] = board[i][j];

                        QString candMove = QString::number(origX) + QString::number(origY) +
                                QString::number(destX) + QString::number(destY);
                        QChar candPiece;

                        // Si es posible el mov. generar sus hijos y obtener la heuristica.
                        if( movementInRule(candMove, piece) ) {
                            if( piece == 'W' ) candPiece = 'B';
                            else if( piece == 'B' ) candPiece = 'W';

                            myBoard[destX][destY] = myBoard[origX][origY];
                            myBoard[origX][origY] = '-';

                            int pts = minimax(myBoard, candPiece, level-1).second;

                            if( level & 1 ) {
                                if( pts < bestPts ) {
                                    bestPts = pts;
                                    bestMove = candMove;
                                }
                            }
                            else {
                                if( pts > bestPts ) {
                                    bestPts = pts;
                                    bestMove = candMove;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if( level != 0 && level != 1) {
        qDebug("Best: %d", bestPts);
        qDebug("Fin del level %d ---------------------------------------------", level);
    }

    return qMakePair( bestMove, bestPts );
}

// cantidad de posibles V's por piezas
// retorna un arreglo la pos i del arreglo dice la cant de posibles i+2 V's
vector<int> Player1::cantPosiblesV(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece)
{
    vector<int> pts;
    pts.push_back(0);
    pts.push_back(0);
    pts.push_back(0);
    pts.push_back(0);

    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {

            if( board[col][row] == piece ) {
                int c = 1;

                // V pa arriba
                try {
                    if( board[col-1][row-1] == piece ) c++;
                    if( board[col-2][row-2] == piece ) c++;
                    if( board[col+1][row-1] == piece ) c++;
                    if( board[col+2][row-2] == piece ) c++;
                    if( c > 1) pts[c-2]++;
                } catch (...) {}

                c = 1;
                // V pa abajo
                try {
                    if( board[col-1][row+1] == piece ) c++;
                    if( board[col-2][row+2] == piece ) c++;
                    if( board[col+1][row+1] == piece ) c++;
                    if( board[col+2][row+2] == piece ) c++;
                    if( c > 1) pts[c-2]++;
                } catch (...) {}
            }
        }
    }

    qDebug("Posibles V'S %d %d %d %d", pts[0], pts[1], pts[2], pts[3]);

    return pts;
}

// return the difference between our pieces and the enemies pieces.
int Player1::ventajaPiezas(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece)
{
    int allies=0, enemies=0;
    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {
            if( board[col][row] == piece ) allies++;
            else if( board[col][row] != '-' ) enemies++;
        }
    }

    //qDebug("Ventaja piezas: %d ", allies - enemies);
    return (allies - enemies);
}

Player1::Player1()
{
    srand( time(NULL) );
}

const QString Player1::getId()
{
    return this->id;
}

void Player1::setId(const QString id)
{
    this->id = id;
}

QString Player1::getMove(const QChar board[BOARD_SIZE][BOARD_SIZE],const QChar piece,const int maxLevel)
{
    // Copy board
    for(int i=0; i<BOARD_SIZE; ++i)
        for(int j=0; j<BOARD_SIZE; ++j)
            myBoard[i][j] = board[i][j];

    QPair<QString, int> res = minimax(myBoard, piece, maxLevel);
    return res.first;
}

QString Player1::getName()
{
    return "Stupid Player 1";
}
