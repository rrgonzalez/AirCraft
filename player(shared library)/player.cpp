#include "player.h"

Player::Player()
{
}

const QString Player::getName()
{
    return this->name;
}

void Player::setName(const QString name)
{
    this->name = name;
}

const QString Player::getId()
{
    return this->id;
}

void Player::setId(const QString id)
{
    this->id = id;
}
