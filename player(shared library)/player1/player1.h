#ifndef PLAYER1_H
#define PLAYER1_H

#define BOARD_SIZE 8

#include "player1_global.h"
#include <QString>
#include <QObject>
#include <time.h>
#include <vector>
using namespace std;

class PLAYER1SHARED_EXPORT Player1 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    QChar myBoard[BOARD_SIZE][BOARD_SIZE];

    bool wonPlayer(const QChar piece);
    bool movementInRule(const QString move, const QChar piece);

    int heuristic(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece);
    QPair<QString, int> minimax(const QChar board[BOARD_SIZE][BOARD_SIZE], QChar piece, int level);

    vector<int> cantPosiblesV(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece);
    int ventajaPiezas(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece);

public:
    Player1();
    const QString getId();
    void setId(const QString id);

public slots:
    QString getMove(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece, const int maxLevel);
    QString getName();
};

#endif // PLAYER1_H
