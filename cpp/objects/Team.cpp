#include "Team.h"

#include "support/Log.h"

Team::Team(QObject *parent)
    : QObject{parent}
    , m_smallPoints{0}
    , m_largePoints{0}
{TRM; DOLTV(SAPF("%p", parent));

}

Team::~Team()
{TRM; DOLT;

    for(auto &playerPtr : m_players)
        playerPtr.clear();
    m_players.clear();
}

QJsonObject Team::serialize() const
{TRM;
    QJsonObject jTeam;
    jTeam[ SERL_TEAM_NAME_KEY ] = m_name;
    jTeam[ SERL_TEAM_SMALL_POINTS_KEY ] = m_smallPoints;
    jTeam[ SERL_TEAM_LARGE_POINTS_KEY ] = m_largePoints;

    QJsonArray jPlayers;
    for(const auto &playerPtr : m_players)
    {
        jPlayers.append( playerPtr->serialize() );
    }
    jTeam[ SERL_PLAYERS_KEY ] = jPlayers;

    return jTeam;
}

void Team::deserialize(const QJsonObject &jTeam)
{TRM;
    this->clear(false);

    m_name = jTeam[ SERL_TEAM_NAME_KEY ].toString();
    emit this->nameChanged();

    m_smallPoints = jTeam[ SERL_TEAM_SMALL_POINTS_KEY ].toInt();
    emit this->smallPointsChanged();

    m_largePoints = jTeam[ SERL_TEAM_LARGE_POINTS_KEY ].toInt();
    emit this->largePointsChanged();

    m_detachedPlayer.clear();
    emit this->detachedPlayerChanged();

    QJsonArray jPlayers = jTeam[ SERL_PLAYERS_KEY ].toArray();
    for(int i=0; i<jPlayers.size(); i++)
    {
        PlayerPtr playerPtr = PlayerPtr::create();
        playerPtr->deserialize( jPlayers[i].toObject() );
        m_players.append( playerPtr );
    }
    emit this->playersChanged();
}

void Team::clear(bool emitting)
{TRM;
    m_name.clear();
    if(emitting) emit this->nameChanged();

    m_smallPoints = 0;
    if(emitting) emit this->smallPointsChanged();

    m_largePoints = 0;
    if(emitting) emit this->largePointsChanged();

    m_detachedPlayer.clear();
    if(emitting) emit this->detachedPlayerChanged();

    m_players.clear();
    if(emitting) emit this->playersChanged();
}

void Team::createDetachedPlayer()
{TRM;
    if(!m_detachedPlayer.isNull())
    {
        W("creating new detached Player, while old wasn't deleted");
    }

    m_detachedPlayer = PlayerPtr::create();
    emit this->detachedPlayerChanged();
}

void Team::deleteDetachedPlayer()
{TRM;
    if(m_detachedPlayer.isNull())
    {
        E("trying to delete aleady deleted detached Player");
        return;
    }

    m_detachedPlayer.clear();
    emit this->detachedPlayerChanged();
}

void Team::validateDetachedPlayer()
{TRM;
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
    for(int i=0; i<m_players.size(); i++)
    {
        if(m_detachedPlayer->getLicense() == m_players[i]->getLicense())
        {
            emit this->detachedPlayerValidationFailed("Player's license is not unique in this team!");
            return;
        }
    }

    emit this->detachedPlayerIsValid();
}

void Team::addDetachedPlayer()
{TRM;
    if(m_detachedPlayer.isNull())
    {
        E("cannot add not existing detached player to list");
        return;
    }

    m_players.append(m_detachedPlayer);
    emit this->playersChanged();

    m_detachedPlayer.clear();
    emit this->detachedPlayerChanged();
}

void Team::deletePlayer(int index)
{TRM;
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

void Team::assignExampleData(const QJsonObject &jTeam)
{TRM;
    m_name = jTeam["name"].toString();

    QJsonArray jPlayers = jTeam["players"].toArray();
    for(int i=0; i<jPlayers.size(); i++)
    {
        QJsonObject jPlayer = jPlayers[i].toObject();

        PlayerPtr player = PlayerPtr::create();
        player->assignExampleData(jPlayer);

        m_players.append(player);
    }
}

void Team::uncheckAllLeaders()
{TRM;
    for(auto &playerPtr : m_players)
        playerPtr->setIsTeamLeader(false);
}

const QString &Team::getName() const
{TRM;
    return m_name;
}

const PlayerPtr &Team::getDetachedPlayer() const
{TRM;
    return m_detachedPlayer;
}

const PlayerPtrList &Team::getPlayers() const
{TRM;
    return m_players;
}

int Team::getSmallPoints() const
{TRM;
    return m_smallPoints;
}

int Team::getLargePoints() const
{TRM;
    return m_largePoints;
}

void Team::setName(const QString &name)
{TRM;
    if(m_name == name)
        return;
    m_name = name;
    emit this->nameChanged();
}

void Team::setSmallPoints(int smallPoints)
{TRM;
    if(m_smallPoints == smallPoints)
        return;

    m_smallPoints = smallPoints;
    emit this->smallPointsChanged();
}

void Team::setLargePoints(int largePoints)
{TRM;
    if(m_largePoints == largePoints)
        return;

    m_largePoints = largePoints;
    emit this->largePointsChanged();
}

void Team::addSmallPoints(int smallPoints)
{TRM;
    if(smallPoints <= 0)
        return;

    m_smallPoints += smallPoints;
    emit this->smallPointsChanged();
}

void Team::addLargePoints(int largePoints)
{TRM;
    if(largePoints <= 0)
        return;

    m_largePoints += largePoints;
    emit this->largePointsChanged();
}

Player *Team::getDetachedPlayerQml() const
{TRM;
    return m_detachedPlayer.data();
}

QmlPlayerPtrVector Team::getPlayersQml() const
{TRM;
    QmlPlayerPtrVector retVec;
    retVec.reserve( m_players.size() );
    for(const auto &playerPtr : m_players)
        retVec.append(playerPtr.data());
    return retVec;
}
