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

void SubPhase::initRounds(QJsonArray jArrangements)
{
    int roundsCount = m_rounds.size() > jArrangements.size() ? jArrangements.size() : m_rounds.size();
    if(m_rounds.size() != jArrangements.size())
    {
        E(QAPF("m_rounds size(%lld) != arrangment size(%lld) using %d size",
               m_rounds.size(), jArrangements.size(), roundsCount))
    }

    for(int i=0; i<roundsCount; i++)
    {
        QJsonArray jArrangement = jArrangements[i].toArray();
        IntPairs arrangement;
        for(int j=0; j<jArrangement.size(); j++)
        {
            int t1 = jArrangement[j].toObject()["t1"].toInt();
            int t2 = jArrangement[j].toObject()["t2"].toInt();
            arrangement.append({t1,t2});
        }

        m_rounds[i] = RoundPtr::create();
        m_rounds[i]->setArrangement(arrangement);
    }
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

bool SubPhase::hasNext() const
{
    // should be called before goToNextRound
    RoundPtr currentRound = m_rounds[m_currentRoundIndex];
    if(currentRound->hasNext())
    {
        return true;
    }

    return (m_currentRoundIndex < m_rounds.size()-1);
}

void SubPhase::goToNext()
{
    // should be called only if hasNextRound return true
    RoundPtr currentRound = m_rounds[m_currentRoundIndex];
    if(currentRound->hasNext())
    {
        currentRound->goToNext();
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
