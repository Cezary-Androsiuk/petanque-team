#include "Team.h"

Team::Team(QObject *parent)
    : QObject{parent}
{
    I(QAPF("Creating Team: %p", this));
}

Team::~Team()
{
    I(QAPF("Destroying Team: %p", this));
}

QJsonObject Team::serialize() const
{
    QJsonObject teamJson;
    teamJson[ SERL_TEAM_NAME_KEY ] = m_name;

    QJsonArray playersJson;
    for(const auto &player : m_players)
    {
        playersJson.append( player->serialize() );
    }
    teamJson[ SERL_PLAYERS_KEY ] = playersJson;

    return teamJson;
}

void Team::deserialize(const QJsonObject &teamJson)
{
    this->clear(false);

    m_name = teamJson[ SERL_TEAM_NAME_KEY ].toString();
    emit this->nameChanged();

    m_detachedPlayer.clear();
    emit this->detachedPlayerChanged();

    QJsonArray playersJson = teamJson[ SERL_PLAYERS_KEY ].toArray();
    for(const auto &playerJson : playersJson)
    {
        PlayerPtr playerPtr = PlayerPtr::create();
        playerPtr->deserialize( playerJson.toObject() );
        m_players.append( playerPtr );
    }
    emit this->playersChanged();
}

void Team::clear(bool emitting)
{
    m_name.clear();
    if(emitting) emit this->nameChanged();

    m_detachedPlayer.clear();
    if(emitting) emit this->detachedPlayerChanged();

    m_players.clear();
    if(emitting) emit this->playersChanged();
}

void Team::createDetachedPlayer()
{
    if(!m_detachedPlayer.isNull())
    {
        W("creating new detached Player, while old wasn't deleted")
    }

    m_detachedPlayer = PlayerPtr::create();
    emit this->detachedPlayerChanged();
}

void Team::deleteDetachedPlayer()
{
    if(m_detachedPlayer.isNull())
    {
        E("trying to delete aleady deleted detached Player")
        return;
    }

    m_detachedPlayer.clear();
    emit this->detachedPlayerChanged();
}

void Team::addDetachedPlayer()
{
    if(m_detachedPlayer.isNull())
    {
        E("cannot add not existing detached player to list")
        return;
    }

    m_players.append(m_detachedPlayer);
    emit this->playersChanged();

    m_detachedPlayer.clear();
    emit this->detachedPlayerChanged();
}

void Team::deletePlayer(int index)
{

    emit this->playersChanged();
}

QString Team::getName() const
{
    return m_name;
}

const PlayerPtr &Team::getDetachedPlayer() const
{
    return m_detachedPlayer;
}

const PlayerPtrList &Team::getPlayers() const
{
    return m_players;
}

void Team::setName(QString name)
{
    if(m_name == name)
        return;
    m_name = name;
    emit this->nameChanged();
}
