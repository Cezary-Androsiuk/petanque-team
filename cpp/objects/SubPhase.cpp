#include "SubPhase.h"

SubPhase::SubPhase(int roundsCount, QObject *parent)
    : QObject{parent}
    , m_currentRound(0)
    , m_rounds(roundsCount, RoundPtr::create())
{
    I(QAPF("Creating SubPhase: %p", this));
    for(const auto &p : m_rounds)
    {
        qDebug() << p;
    }
}

SubPhase::~SubPhase()
{
    I(QAPF("Destroying SubPhase: %p", this));
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
        D("round has next roundStage")
        return true;
    }

    D("round doesn't have next roundStage")
    return (m_currentRound < m_rounds.size()-1);
}

void SubPhase::goToNextRound()
{
    // should be called only if hasNextRound return true
    RoundPtr currentRound = m_rounds[m_currentRound];
    qDebug() << currentRound;
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
