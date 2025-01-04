#include "SubPhase.h"

SubPhase::SubPhase(int roundsCount, QObject *parent)
    : QObject{parent}
    , m_currentRoundIndex{0}
    , m_rounds(roundsCount, RoundPtr())
{
    DOLTV(this, QString::number(roundsCount));
}

SubPhase::~SubPhase()
{
    DOLT(this)
}

void SubPhase::onStart()
{
    D(QAPF("before subPhase start: %p", this), Log::Action::SaveSession)
    this->roundStart();
}

void SubPhase::onEnd()
{
    D(QAPF("after subPhase end: %p", this), Log::Action::SaveSession)
    this->roundEnd();
}

void SubPhase::initRounds(QJsonArray jArrangements)
{
    D(QAPF("init rounds: %p", this), Log::Action::SaveSession)

    int roundsCount = m_rounds.size() > jArrangements.size() ? jArrangements.size() : m_rounds.size();
    /// if rounds count not equal to arrangement count, display error and use least value
    if(m_rounds.size() != jArrangements.size())
    {
        E(QAPF("m_rounds size(%lld) != arrangment size(%lld) using %d size",
               m_rounds.size(), jArrangements.size(), roundsCount))
    }

    /// for each round set their part of berger's table
    for(int i=0; i<roundsCount; i++)
    {
        QJsonArray jArrangement = jArrangements[i].toArray();
        IntPairs arrangement;
        /// change json to int pairs
        /// -1 is to change team numbers to intexes
        for(int j=0; j<jArrangement.size(); j++)
        {
            int t1 = jArrangement[j].toObject()["t1"].toInt() -1;
            int t2 = jArrangement[j].toObject()["t2"].toInt() -1;
            arrangement.append({t1,t2});
        }

        m_rounds[i] = RoundPtr::create(m_teams);
        m_rounds[i]->setArrangement(arrangement);
        m_rounds[i]->initMatches();
    }
    emit this->roundsChanged();
}

QJsonObject SubPhase::serialize() const
{
    QJsonObject jSubPhase;

    jSubPhase[ SERL_SUB_PHASE_NAME_KEY ] = m_name;
    jSubPhase[ SERL_CURRENT_ROUND_INDEX_KEY ] = m_currentRoundIndex;

    QJsonArray jRounds;
    for(const auto &roundPtr : m_rounds)
    {
        if(roundPtr.isNull())
        {
            W("cannot serialize not existing round")
            jRounds.append( QJsonObject() );
        }
        else jRounds.append( roundPtr->serialize() );
    }
    jSubPhase[ SERL_ROUNDS_KEY ] = jRounds;

    return jSubPhase;
}

void SubPhase::deserialize(const QJsonObject &jSubPhase)
{
    this->clear(false);

    if(!jSubPhase.contains(SERL_SUB_PHASE_NAME_KEY))
    {
        W("cannot deserialize name of sub phase");
    }
    else
    {
        this->setName( jSubPhase[ SERL_SUB_PHASE_NAME_KEY ].toString() );
    }

    if(!jSubPhase.contains(SERL_CURRENT_ROUND_INDEX_KEY))
    {
        W("cannot deserialize current round index of sub phase");
    }
    else
    {
        m_currentRoundIndex = jSubPhase[ SERL_CURRENT_ROUND_INDEX_KEY ].toInt();
        emit this->currentRoundIndexChanged();
    }

    this->deserializeRounds(jSubPhase);
}

void SubPhase::deserializeRounds(const QJsonObject &jSubPhase)
{
    if(!jSubPhase.contains(SERL_ROUNDS_KEY))
    {
        E("cannot deserialize rounds due to missing key in json: " SERL_ROUNDS_KEY)
        return;
    }

    QJsonArray jRounds = jSubPhase[ SERL_ROUNDS_KEY ].toArray();

    if(m_rounds.size() != jRounds.size())
    {
        E(QAPF("cannot deserialize rounds due to inconsistent size: "
               "m_rounds(%lld) list and jRounds(%lld) list",
               m_rounds.size(), jRounds.size() ))
        return;
    }

    for(int i=0; i<m_rounds.size(); i++)
    {
        if(m_rounds[i].isNull())
            E("cannot deserialize, due to not exiting round")
        else
            m_rounds[i]->deserialize( jRounds[i].toObject() );
    }
}

void SubPhase::clear(bool emitting)
{

}

bool SubPhase::verify(QString &message) const
{
    if( !(m_rounds[m_currentRoundIndex]->verify(message)) )
    {
        message = "in round "+QString::number(m_currentRoundIndex)+": " + message;
        return false;
    }
    return true;
}

bool SubPhase::hasNext() const
{
    // should be called before goToNextRound
    const RoundPtr &currentRound = m_rounds[m_currentRoundIndex];
    if(currentRound->hasNext())
    {
        return true;
    }

    return (m_currentRoundIndex < m_rounds.size()-1);
}

void SubPhase::goToNext()
{
    // should be called only if hasNextRound return true
    RoundPtr &currentRound = m_rounds[m_currentRoundIndex];
    if(currentRound->hasNext())
    {
        currentRound->goToNext();
    }
    else
    {
        this->roundEnd();

        m_currentRoundIndex ++;
        emit this->currentRoundIndexChanged();
        D("starting round: " + QString::number(m_currentRoundIndex, Log::Action::SaveSession),
          Log::Action::SaveSession);

        this->roundStart();
    }
}

void SubPhase::assignExampleData()
{
    if(m_rounds.size() <= m_currentRoundIndex)
    {
        E(QAPF("cannot read index out of bounds: m_rounds %lld, m_currentRoundIndex %d",
               m_rounds.size(), m_currentRoundIndex))
        return;
    }

    /// only current round
    m_rounds[m_currentRoundIndex]->assignExampleData();
}

void SubPhase::roundStart()
{
    m_rounds[m_currentRoundIndex]->onStart();
}

void SubPhase::roundEnd()
{
    m_rounds[m_currentRoundIndex]->onEnd();
}

QString SubPhase::getName() const
{
    return m_name;
}

int SubPhase::getCurrentRoundIndex() const
{
    return m_currentRoundIndex;
}

const RoundPtrVector &SubPhase::getRounds() const
{
    return m_rounds;
}

Round *SubPhase::getCurrentRound() const
{
    return m_rounds[m_currentRoundIndex].data();
}

QmlRoundPtrVector SubPhase::getRoundsQml() const
{
    QmlRoundPtrVector retVec;
    retVec.reserve(m_rounds.size());
    for(const auto &roundPtr : m_rounds)
        retVec.append(roundPtr.data());
    return retVec;
}

void SubPhase::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

void SubPhase::setTeams(const TeamPtrList &teams)
{
    m_teams.clear();
    for(const auto &team : teams)
        m_teams.append(team);
    emit this->teamsChanged();
}
