#ifndef COMPUTERVSCOMPUTER_H
#define COMPUTERVSCOMPUTER_H

#define BOARD_SIZE 8

#include <QObject>
#include "player1.h"
#include "player2.h"

class ComputerVsComputer : public QObject
{
    Q_OBJECT
    QChar board[BOARD_SIZE][BOARD_SIZE];
    QString gameResult;

    bool wonPlayer(const char piece);
    bool movementInRule(const QString move, const QChar piece);
    bool draw();
    void movePiece(QString move);
    void tryEat(int player);
    Player1* player1;
    Player2* player2;

public:
    ComputerVsComputer();

public slots:
    void init();
    QString player1Name();
    QString player2Name();
    QString nextMovePlayer1();
    QString nextMovePlayer2();
    QString getGameResult();
};

#endif // COMPUTERVSCOMPUTER_H
