#include "SubPhase.h"

SubPhase::SubPhase(int roundsCount, QObject *parent)
    : QObject{parent}
    , m_currentRound(0)
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
    if( !(m_rounds[m_currentRound]->verify(message)) )
    {
        message = "in round "+QString::number(m_currentRound)+": " + message;
        return false;
    }
    return true;
}

bool SubPhase::hasNextRound() const
{
    // should be called before goToNextRound
    RoundPtr currentRound = m_rounds[m_currentRound];
    if(currentRound->hasNextRoundStage())
    {
        return true;
    }

    return (m_currentRound < m_rounds.size()-1);
}

void SubPhase::goToNextRound()
{
    // should be called only if hasNextRound return true
    RoundPtr currentRound = m_rounds[m_currentRound];
    if(currentRound->hasNextRoundStage())
    {
        currentRound->goToNextRoundStage();
    }
    else
    {
        m_currentRound ++;
        D("going to         round: " + QString::number(m_currentRound));
    }
}

QString SubPhase::getName() const
{
    return m_name;
}

void SubPhase::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
