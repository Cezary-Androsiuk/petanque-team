#include "Phase.h"

#include "support/Log.h"
#include "storages/Personalization.h"

Phase::Phase(PhaseEnum phase, QObject *parent)
    : QObject{parent}
    , m_phase{phase}
{TRM; DOLTV(SAPF("%s, %p", EnumConvert::PhaseToQString(phase).toStdString().c_str(), parent));

}

Phase::~Phase()
{TRM; DOLT;

}

void Phase::onStart()
{TRM;
    DA(Log::Action::SaveSession, "before phase start: %p", this);
    this->subPhaseStart();
}

void Phase::onEnd()
{TRM;
    DA(Log::Action::SaveSession, "after phase end: %p", this);
    this->subPhaseEnd();
}

void Phase::initSubPhases(const TeamPtrLists &listsOfTeams)
{TRM;
    Personalization *const p = Personalization::getInstance();
    const QJsonObject &roundsMatches = p->getRoundsMatches();

    if(m_phase == PhaseEnum::First)
    {
        QJsonArray arrangement = roundsMatches["phase 1"].toArray();

        if(listsOfTeams.size() != 1)
        {
            E("invalid listOfTeams size, required 1, but got %lld", listsOfTeams.size());
            return;
        }

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setTeams(listsOfTeams[0]);
        m_subPhases[0]->setName("1");
        m_subPhases[0]->initRounds(arrangement);
    }
    else // m_phase == PhaseEnum::Second
    {
        QJsonArray arrangement = roundsMatches["phase 2"].toArray();

        if(listsOfTeams.size() != 2)
        {
            E("invalid listOfTeams size, required 2, but got %lld", listsOfTeams.size());
            return;
        }

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setTeams(listsOfTeams[0]);
        m_subPhases[0]->setName("2a");
        m_subPhases[0]->initRounds(arrangement);

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[1]->setTeams(listsOfTeams[1]);
        m_subPhases[1]->setName("2b");
        m_subPhases[1]->initRounds(arrangement);
    }
}

QJsonObject Phase::serialize() const
{TRM;
    QJsonObject jPhase;

    /// m_phase - don't need to be serialized

    QJsonArray jSubPhases;
    for(const auto &subPhasePtr : m_subPhases)
    {
        if(subPhasePtr.isNull())
        {
            W("cannot serialize not existing sub phase");
            jSubPhases.append( QJsonObject() );
        }
        else jSubPhases.append( subPhasePtr->serialize() );
    }
    jPhase[ SERL_SUB_PHASES_KEY ] = jSubPhases;

    return jPhase;
}

void Phase::deserialize(const QJsonObject &jPhase)
{TRM;
    this->clear(false);

    /// m_phase - don't need to be deserialized

    this->deserializeSubPhases(jPhase);
}

void Phase::deserializeSubPhases(const QJsonObject &jPhase)
{TRM;
    if(!jPhase.contains( SERL_SUB_PHASES_KEY ))
    {
        E("cannot deserialize subphases due to missing key in json: " SERL_SUB_PHASES_KEY);
        return;
    }

    QJsonArray jSubPhases = jPhase[ SERL_SUB_PHASES_KEY ].toArray();

    if(m_subPhases.size() != jSubPhases.size())
    {
        E("cannot deserialize subphases due to inconsistent size: "
          "m_subPhases(%lld) list and jSubPhases(%lld) list",
          m_subPhases.size(), jSubPhases.size() );
        return;
    }

    for(int i=0; i<m_subPhases.size(); i++)
    {
        if(m_subPhases[i].isNull())
            E("cannot deserialize, due to not existing subPhase");
        else
            m_subPhases[i]->deserialize( jSubPhases[i].toObject() );
    }
}

void Phase::clear(bool emitting)
{TRM;

}

void Phase::verify()
{TRM;
    for(int i=0; i<m_subPhases.size(); i++)
    {
        QString message;
        if(!m_subPhases[i]->verify(message))
        {
            QString prefix( "In "+ m_subPhases[i]->getName() +" phase: " );
            emit this->verificationFailed(prefix + message);
            return;
        }
    }
    emit this->verified();
}

bool Phase::hasNext()
{TRM;
    bool hasNextRound = true;
    for(int i=0; i<m_subPhases.size(); i++)
    {
        if(!m_subPhases[i]->hasNext())
        {
            hasNextRound = false;
            break;
        }
    }
    return hasNextRound;
}

void Phase::goToNext()
{TRM;
    if(!this->hasNext())
    {
        W("trying to go next, where is no next");
        return;
    }

    for(auto &subPhasePtr : m_subPhases)
    {
        subPhasePtr->goToNext();
    }
}

void Phase::assignExampleData()
{TRM;
    /// for all subPhases
    for(auto &subPhasePtr : m_subPhases)
        subPhasePtr->assignExampleData();
}

void Phase::subPhaseStart()
{TRM;
    for(auto &subPhase : m_subPhases)
        subPhase->onStart();
}

void Phase::subPhaseEnd()
{TRM;
    for(auto &subPhase : m_subPhases)
        subPhase->onEnd();
}

int Phase::getSubPhasesCount() const
{TRM;
    return m_subPhases.size();
}

const SubPhasePtrVector &Phase::getSubPhases() const
{TRM;
    return m_subPhases;
}

QString Phase::getCurrentName() const
{TRM;
    /// Prevent crashing app
    if(Q_UNLIKELY(m_subPhases.size() < 1))
    {
        E("empty m_subPhases vector, cannot determine round stage");
        return "---";
    }

    /// returned right before changing Round or RoundStage
    /// phase is a container for supPages
    /// and doesn't have second stage or something like that
    return m_subPhases[0]->getCurrentName();
}

QString Phase::getNextName() const
{TRM;
    /// Prevent crashing app
    if(Q_UNLIKELY(m_subPhases.size() < 1))
    {
        E("empty m_subPhases vector, cannot determine round stage");
        return "---";
    }

    /// returned right before changing Round or RoundStage
    /// phase is a container for supPages
    /// and doesn't have second stage or something like that
    return m_subPhases[0]->getNextName();
}

QmlSubPhasePtrVector Phase::getSubPhasesQml() const
{TRM;
    QmlSubPhasePtrVector retVec;
    retVec.reserve( m_subPhases.size() );
    for(const auto &subPhasePtr : m_subPhases)
        retVec.append(subPhasePtr.data());
    return retVec;
}
