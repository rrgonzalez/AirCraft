#ifndef PERSONVSCOMPUTER_H
#define PERSONVSCOMPUTER_H

#define BOARD_SIZE 8

#include <QObject>
#include "player1.h"

class PersonVsComputer : public QObject
{
    Q_OBJECT

    QChar board[BOARD_SIZE][BOARD_SIZE];
    QString gameResult;

    Q_PROPERTY(QString personName READ getPersonName WRITE setPersonName)
    QString personName;

    bool movementInRule(const QString move, const QChar piece);
    bool draw();
    Player1* player1;

public:
    PersonVsComputer();

    QString getPersonName() const;
    void setPersonName(const QString &value);

public slots:
    void init();
    QString player1Name();
    QString nextMovePlayer1();
    QString getGameResult();
    bool movePiece(QString move);
    bool wonPlayer(const QString param_piece);
    QString tryEat(int player);
};

#endif // PERSONVSCOMPUTER_H
