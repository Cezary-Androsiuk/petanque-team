#include "SubPhase.h"

SubPhase::SubPhase(int roundsCount, QObject *parent)
    : QObject{parent}
    , m_currentRoundIndex(0)
    , m_rounds(roundsCount)
{
    DOLTV(this, QString::number(roundsCount));
    for(auto &roundPtr : m_rounds)
    {
        roundPtr = RoundPtr::create();
    }
}

SubPhase::~SubPhase()
{
    DOLT(this)
}

QJsonObject SubPhase::serialize() const
{
    return QJsonObject();
}

void SubPhase::deserialize(const QJsonObject &data)
{

}

void SubPhase::clear()
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

bool SubPhase::hasNextRound() const
{
    // should be called before goToNextRound
    RoundPtr currentRound = m_rounds[m_currentRoundIndex];
    if(currentRound->hasNextRoundStage())
    {
        return true;
    }

    return (m_currentRoundIndex < m_rounds.size()-1);
}

void SubPhase::goToNextRound()
{
    // should be called only if hasNextRound return true
    RoundPtr currentRound = m_rounds[m_currentRoundIndex];
    if(currentRound->hasNextRoundStage())
    {
        currentRound->goToNextRoundStage();
    }
    else
    {
        m_currentRoundIndex ++;
        emit this->currentRoundIndexChanged();
        D("going to         round: " + QString::number(m_currentRoundIndex));
    }
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
