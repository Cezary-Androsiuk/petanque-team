#include "Match.h"

#include "support/Log.h"
#include "objects/MatchSingles.h"
#include "objects/MatchDoubles.h"
#include "objects/MatchTriples.h"

Match::Match(RoundStageEnumRPtr roundStageRef, QObject *parent)
    : QObject{parent}
    , m_matchTypes(3, MatchTypeBasePtr())
    , m_currentRoundStage{roundStageRef}
{TRM; DOLTV(SAPF("%s, %p", EnumConvert::RoundStageToQString(*roundStageRef).toStdString().c_str(), parent));

}

Match::~Match()
{TRM; DOLT;

}

void Match::onStart()
{TRM;
    DA(Log::Action::SaveSession, "before match start: %p", this);

    if(*m_currentRoundStage == RoundStageEnum::RoundSummary)
        return;

    MatchTypeBasePtr currentMatchType = m_matchTypes[(*m_currentRoundStage)/2];
    bool isSelectionStage = (*m_currentRoundStage)%2 == 0;

    if(currentMatchType.isNull())
    {
        W("currentMatchType is a null");
        return;
    }

    if(isSelectionStage)
        currentMatchType->onSelectionStart();
    else
        currentMatchType->onMatchStart();
}

void Match::onEnd()
{TRM;
    DA(Log::Action::SaveSession, "after match end: %p", this);

    if(*m_currentRoundStage == RoundStageEnum::RoundSummary)
        return;

    MatchTypeBasePtr currentMatchType = m_matchTypes[(*m_currentRoundStage)/2];
    bool isSelectionStage = (*m_currentRoundStage)%2 == 0;

    if(currentMatchType.isNull())
    {
        W("currentMatchType is a null");
        return;
    }

    if(isSelectionStage)
        currentMatchType->onSelectionEnd();
    else
        currentMatchType->onMatchEnd();
}

void Match::initMatchesTypes()
{TRM;
    DA(Log::Action::SaveSession, "init matchTypes: %p", this);

    m_matchTypes[0] = MatchSinglesPtr::create(m_teamLeft, m_teamRight);

    m_matchTypes[1] = MatchDoublesPtr::create(m_teamLeft, m_teamRight);

    m_matchTypes[2] = MatchTriplesPtr::create(m_teamLeft, m_teamRight);
}

QJsonObject Match::serialize() const
{TRM;
    QJsonObject jMatch;

    jMatch[ SERL_MATCH_TEAM_LEFT_NAME_KEY ] = this->serializeTeam(m_teamLeft);
    jMatch[ SERL_MATCH_TEAM_RIGHT_NAME_KEY ] = this->serializeTeam(m_teamRight);
    /// m_currentRoundStage - don't need to be deserialized

    QJsonObject jMatchTypes;
    jMatchTypes[ SERL_MATCH_TYPE_SINGLES_KEY ] = this->serializeMatchType(0);
    jMatchTypes[ SERL_MATCH_TYPE_DOUBLES_KEY ] = this->serializeMatchType(1);
    jMatchTypes[ SERL_MATCH_TYPE_TRIPLES_KEY ] = this->serializeMatchType(2);
    jMatch[ SERL_MATCH_TYPES_KEY ] = jMatchTypes;
    return jMatch;
}

void Match::deserialize(const QJsonObject &jMatch)
{TRM;
    this->clear(false);

    /// m_teamLeft - don't need to be deserialized
    /// m_teamRight - don't need to be deserialized
    /// m_currentRoundStage - don't need to be deserialized

    this->deserializeMatchTypes(jMatch);

    emit this->currentRoundStageChanged();
}

void Match::clear(bool emitting)
{TRM;

}

QString Match::serializeTeam(const TeamWPtr &teamWPtr) const
{TRM;
    if(teamWPtr.isNull())
    {
        W("cannot serialize team in match due to not existing team");
        return QString();
    }

    TeamPtr teamPtr = teamWPtr.toStrongRef();
    return teamPtr->getName();
}

QJsonObject Match::serializeMatchType(int matchTypeIndex) const
{TRM;
    if(m_matchTypes.size() <= matchTypeIndex)
    {
        E("matchTypeIndex is %d, but m_matchTypes.size() is %lld",
          matchTypeIndex, m_matchTypes.size());
        return QJsonObject();
    }

    if(m_matchTypes[matchTypeIndex].isNull())
    {
        W("cannot serialize not exising match type");
        return QJsonObject();
    }

    return m_matchTypes[matchTypeIndex]->serialize();
}

void Match::deserializeMatchTypes(const QJsonObject &jMatch)
{TRM;
    if(!jMatch.contains( SERL_MATCH_TYPES_KEY ))
    {
        E("cannot deserialize match types due to missing key: " SERL_MATCH_TYPES_KEY);
        return;
    }

    QJsonObject jMatchTypes = jMatch[ SERL_MATCH_TYPES_KEY ].toObject();

    if(!jMatchTypes.contains( SERL_MATCH_TYPE_SINGLES_KEY ))
        E("cannot deserialize match types singles due to missing key: " SERL_MATCH_TYPE_SINGLES_KEY);
    else if(m_matchTypes[0].isNull())
        E("cannot deserialize due to not existing match type singles");
    else
        m_matchTypes[0]->deserialize( jMatchTypes[ SERL_MATCH_TYPE_SINGLES_KEY ].toObject() );


    if(!jMatchTypes.contains( SERL_MATCH_TYPE_DOUBLES_KEY ))
        E("cannot deserialize match types doubles due to missing key: " SERL_MATCH_TYPE_DOUBLES_KEY);
    else if(m_matchTypes[1].isNull())
        E("cannot deserialize due to not existing match type doubles");
    else
        m_matchTypes[1]->deserialize( jMatchTypes[ SERL_MATCH_TYPE_DOUBLES_KEY ].toObject() );


    if(!jMatchTypes.contains( SERL_MATCH_TYPE_TRIPLES_KEY ))
        E("cannot deserialize match types triples due to missing key: " SERL_MATCH_TYPE_TRIPLES_KEY);
    else if(m_matchTypes[2].isNull())
        E("cannot deserialize due to not existing match type triples");
    else
        m_matchTypes[2]->deserialize( jMatchTypes[ SERL_MATCH_TYPE_TRIPLES_KEY ].toObject() );
}

bool Match::verify(QString &message) const
{TRM;
    if(*m_currentRoundStage == RoundStageEnum::RoundSummary)
        return true;

    MatchTypeBasePtr currentMatchType = m_matchTypes[(*m_currentRoundStage)/2];
    bool isSelectionStage = (*m_currentRoundStage)%2 == 0;

    if(isSelectionStage)
    {
        if(!currentMatchType->verifySelection(message))
        {
            QString roundStage = EnumConvert::RoundStageToQString(*m_currentRoundStage);
            message = "in roundStage " + roundStage + ": " + message;
            return false;
        }
    }
    else
    {
        if(!currentMatchType->verifyMatch(message))
        {
            QString roundStage = EnumConvert::RoundStageToQString(*m_currentRoundStage);
            message = "in roundStage " + roundStage + ": " + message;
            return false;
        }
    }

    return true;
}

void Match::assignExampleData()
{TRM;
    if(*m_currentRoundStage == RoundStageEnum::RoundSummary)
        return;

    MatchTypeBasePtr currentMatchType = m_matchTypes[(*m_currentRoundStage)/2];
    bool isSelectionStage = (*m_currentRoundStage)%2 == 0;

    /// assign only for current matchType
    if(isSelectionStage)
        currentMatchType->assignSelectionExampleData();
    else
        currentMatchType->assignMatchExampleData();
}

Team *Match::getTeamLeft() const
{TRM;
    return m_teamLeft.data();
}

Team *Match::getTeamRight() const
{TRM;
    return m_teamRight.data();
}

MatchTypeBase *Match::getCurrentMatchType() const
{TRM;
    return m_matchTypes[(*m_currentRoundStage)/2].data();
}

void Match::setTeamLeft(const TeamPtr &team)
{TRM;
    m_teamLeft = team;
}

void Match::setTeamRight(const TeamPtr &team)
{TRM;
    m_teamRight = team;
}
