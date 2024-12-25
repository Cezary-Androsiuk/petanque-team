#include "Round.h"

Round::Round(QObject *parent)
    : QObject{parent}
    , m_currentRoundStage{RoundStageEnum::SingielsSelection}
{
    DOLT(this)

}

Round::~Round()
{
    DOLT(this)

}

void Round::initMatches()
{
    const TeamPtrList &teams = globalTeams;
    const int teamSize = teams.size();

    m_matches.reserve(m_arrangement.size());
    for(int i=0; i<m_arrangement.size(); i++)
    {
        // D("creating "+ QString::number(i) +" match")
        const auto &matchArrangement = m_arrangement[i];
        int t1 = matchArrangement.first;
        int t2 = matchArrangement.second;
        if(t1 >= teamSize || t2 >= teamSize)
        {
            W(QAPF("cannot assing team to match t1(%d), t2(%d), teamSize(%d),"
                   " then match will not be created", t1, t2, teamSize))
            continue;
        }

        MatchPtr match = MatchPtr::create(m_currentRoundStage);
        QObject::connect(
            this, &Round::currentRoundStageChanged,
            match.data(), &Match::currentRoundStageChanged);
        match->setTeamLeft(teams[t1]);
        match->setTeamRight(teams[t2]);
        match->initMatchesTypes();

        m_matches.append(match);
    }

    emit this->matchesChanged();
}

QJsonObject Round::serialize() const
{
    QJsonObject jRound;

    jRound[ SERL_CURRENT_ROUND_STAGE_KEY ] = EnumConvert::RoundStageToQString(m_currentRoundStage);

    QJsonArray jArrangement;
    for(const auto &matchArrangement : m_arrangement)
    {
        QJsonObject jMatchArrangement;
        jMatchArrangement[ SERL_ARRANGEMENT_MATCH_FIRST_KEY ] = matchArrangement.first;
        jMatchArrangement[ SERL_ARRANGEMENT_MATCH_SECOND_KEY ] = matchArrangement.second;
        jArrangement.append(jMatchArrangement);
    }
    jRound[ SERL_ARRANGEMENT_KEY ] = jArrangement;

    QJsonArray jMatches;
    for(const auto &matchPtr : m_matches)
    {
        if(matchPtr.isNull())
        {
            W("cannot serialize not existing match")
            jMatches.append( QJsonObject() );
        }
        else jMatches.append( matchPtr->serialize() );
    }
    jRound[ SERL_MATCHES_KEY ] = jMatches;

    return jRound;
}

void Round::deserialize(const QJsonObject &jRound)
{
    this->clear(false);

    if(!jRound.contains(SERL_CURRENT_ROUND_STAGE_KEY))
    {
        E("cannot deserialize current round stage, due to not existing key: " SERL_CURRENT_ROUND_STAGE_KEY);
    }
    else m_currentRoundStage = EnumConvert::QStringToRoundStage( jRound[ SERL_CURRENT_ROUND_STAGE_KEY ].toString() );
    emit this->currentRoundStageChanged();

    /// m_arrangement - don't need to be deserialized

    this->deserializeMatches(jRound);
}

void Round::deserializeMatches(const QJsonObject &jRound)
{
    if(!jRound.contains( SERL_MATCHES_KEY ))
    {
        E("cannot deserialize matches due to missing key in json: " SERL_MATCHES_KEY)
        return;
    }

    QJsonArray jMatches = jRound[ SERL_MATCHES_KEY ].toArray();

    if(m_matches.size() != jMatches.size())
    {
        E(QAPF("cannot deserialize matches due to inconsistent size: "
               "m_matches(%lld) list and jMatches(%lld) list",
               m_matches.size(), jMatches.size() ))
        return;
    }

    for(int i=0; i<m_matches.size(); i++)
    {
        if(m_matches[i].isNull())
            E("cannot deserialize, due to not exising match")
        else
            m_matches[i]->deserialize( jMatches[i].toObject() );
    }

    emit this->matchesChanged();
}

void Round::clear(bool emitting)
{

}

bool Round::verify(QString &message) const
{
    for(int i=0; i<m_matches.size(); i++)
    {
        if(!(m_matches[i]->verify(message)))
        {
            message = "in match " + QString::number(i) + ": " + message;
            return false;
        }
    }
    return true;
}

bool Round::hasNext() const
{
    // should be called before goToNextRoundStage
    return (m_currentRoundStage != RoundStageEnum::RoundSummary);
}

void Round::goToNext()
{
    m_currentRoundStage = static_cast<RoundStageEnum>(m_currentRoundStage+1);
    emit this->currentRoundStageChanged();
}

void Round::assignExampleData()
{
    for(auto &matchPtr : m_matches)
        matchPtr->assignExampleData();
}

RoundStageEnum Round::getCurrentRoundStage() const
{
    return m_currentRoundStage;
}

MatchPtrVectorQml Round::getMatchesQml() const
{
    MatchPtrVectorQml retVec;
    retVec.reserve(m_matches.size());
    for(const auto &matchPtr : m_matches)
        retVec.append(matchPtr.data());
    return retVec;
}

void Round::setArrangement(const IntPairs &arrangement)
{
    m_arrangement = arrangement;
    // D(QAPF("set arrangement for %p Round:", this))
    // for(const auto &pair : m_arrangement)
    // {
    //     D(QAPF("%d %d", pair.first, pair.second))
    // }
}
