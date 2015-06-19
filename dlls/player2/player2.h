#ifndef PLAYER2_H
#define PLAYER2_H

#define BOARD_SIZE 8

#include "player2_global.h"
#include <QString>
#include <QObject>
#include <time.h>

class PLAYER2SHARED_EXPORT Player2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    QChar myBoard[BOARD_SIZE][BOARD_SIZE];

    bool wonPlayer(const QChar piece);
    bool movementInRule(const QString move, const QChar piece);

public:
    Player2();
    const QString getId();
    void setId(const QString id);

public slots:
    QString getMove(const QChar board[BOARD_SIZE][BOARD_SIZE], const QChar piece, const int maxLevel);
    QString getName();
};

#endif // PLAYER2_H
