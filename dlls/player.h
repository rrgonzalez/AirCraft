#ifndef PLAYER_H
#define PLAYER_H

#include "player_global.h"
#include <QString>
#include <QObject>

class PLAYERSHARED_EXPORT Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    QString name;
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    QString id;

public:
    Player();
    const QString getName();
    void setName(const QString name);
    const QString getId();
    void setId(const QString id);

signals:
    void nameChanged();
    void idChanged();
};

#endif // PLAYER_H
