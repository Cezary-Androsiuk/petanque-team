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

void Team::validateDetachedPlayer()
{
    if(m_detachedPlayer.isNull())
    {
        const char *message = "Detached Player not exist";
        E(message);
        emit this->detachedPlayerValidationFailed(message);
        return;
    }

    /// Check if the fields are empty
    if(m_detachedPlayer->getFirstName().isEmpty())
    {
        emit this->detachedPlayerValidationFailed("Player required first name");
        return;
    }
    if(m_detachedPlayer->getLastName().isEmpty())
    {
        emit this->detachedPlayerValidationFailed("Player required last name");
        return;
    }
    if(m_detachedPlayer->getLicense().isEmpty())
    {
        emit this->detachedPlayerValidationFailed("Player required license");
        return;
    }

    /// Check unique parameter
    for(const auto &playerPtr : m_players)
    {
        if(m_detachedPlayer->getLicense() == playerPtr->getLicense())
        {
            emit this->detachedPlayerValidationFailed("Player's license is not unique in this team!");
            return;
        }
    }

    emit this->detachedPlayerIsValid();
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
    if(m_players.size() <= index)
    {
        QString sSize = QString::number(m_players.size());
        QString sIndex = QString::number(index);
        E("trying to delete not existing player("+sIndex+") from list("+sSize+")");
        return;
    }

    m_players.remove(index);
    emit this->playersChanged();
}

void Team::createExamplePlayers()
{
    E("NOT FINISHED");
}

void Team::uncheckAllLeaders()
{
    for(auto &playerPtr : m_players)
        playerPtr->setIsTeamLeader(false);
}

const QString &Team::getName() const
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

void Team::setName(const QString &name)
{
    if(m_name == name)
        return;
    m_name = name;
    emit this->nameChanged();
}

Player *Team::getDetachedPlayerQml() const
{
    return m_detachedPlayer.data();
}

QmlPlayerPtrVector Team::getPlayersQml() const
{
    QmlPlayerPtrVector retVec;
    retVec.reserve( m_players.size() );
    for(const auto &playerPtr : m_players)
        retVec.append(playerPtr.data());
    return retVec;
}
