#include "Round.h"

#include "support/Log.h"

Round::Round(TeamPtrList &teams, QObject *parent)
    : QObject{parent}
    , m_teams{teams}
    , m_currentRoundStage{RoundStageEnum::SinglesSelection}
{TRM; DOLTV(SAPF("%s, %p",
               [&](){
                   std::string t = "[";
                   for(int i=0;i<teams.size();i++)
                       t += SAPF("%p, ", teams[i].data()).toStdString();
                   if(!teams.empty()) t.resize(t.size() - 2);
                   return t + "]";
               }().c_str(),
               parent));

}

Round::~Round()
{TRM; DOLT;

}

void Round::onStart()
{TRM;
    DA(Log::Action::SaveSession, "before round start: %p", this);

    this->matchStart();
}

void Round::onEnd()
{TRM;
    DA(Log::Action::SaveSession, "after round end: %p", this);
    this->matchEnd();
}

void Round::initMatches()
{TRM;
    DA(Log::Action::SaveSession, "init matches: %p", this);

    const int teamSize = m_teams.size();

    m_matches.reserve(m_arrangement.size());
    for(int i=0; i<m_arrangement.size(); i++)
    {
        // D("creating "+ QString::number(i) +" match")
        const auto &matchArrangement = m_arrangement[i];
        int t1 = matchArrangement.first;
        int t2 = matchArrangement.second;
        if(t1 >= teamSize || t2 >= teamSize)
        {
            W("cannot assing team to match t1(%d), t2(%d), teamSize(%d),"
              " then match will not be created", t1, t2, teamSize);
            continue;
        }

        MatchPtr match = MatchPtr::create(&m_currentRoundStage);
        QObject::connect(
            this, &Round::currentRoundStageChanged,
            match.data(), &Match::currentRoundStageChanged);
        match->setTeamLeft(m_teams[t1]);
        match->setTeamRight(m_teams[t2]);
        match->initMatchesTypes();

        m_matches.append(match);
    }

    emit this->matchesChanged();
}

QJsonObject Round::serialize() const
{TRM;
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
            W("cannot serialize not existing match");
            jMatches.append( QJsonObject() );
        }
        else jMatches.append( matchPtr->serialize() );
    }
    jRound[ SERL_MATCHES_KEY ] = jMatches;

    return jRound;
}

void Round::deserialize(const QJsonObject &jRound)
{TRM;
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
{TRM;
    if(!jRound.contains( SERL_MATCHES_KEY ))
    {
        E("cannot deserialize matches due to missing key in json: " SERL_MATCHES_KEY);
        return;
    }

    QJsonArray jMatches = jRound[ SERL_MATCHES_KEY ].toArray();

    if(m_matches.size() != jMatches.size())
    {
        E("cannot deserialize matches due to inconsistent size: "
          "m_matches(%lld) list and jMatches(%lld) list",
          m_matches.size(), jMatches.size() );
        return;
    }

    for(int i=0; i<m_matches.size(); i++)
    {
        if(m_matches[i].isNull())
            E("cannot deserialize, due to not exising match");
        else
            m_matches[i]->deserialize( jMatches[i].toObject() );
    }

    emit this->matchesChanged();
}

void Round::clear(bool emitting)
{TRM;

}

bool Round::verify(QString &message) const
{TRM;
    for(int i=0; i<m_matches.size(); i++)
    {
        if(!(m_matches[i]->verify(message)))
        {
            message = "in match " + QString::number(i+1) + ": " + message;
            return false;
        }
    }
    return true;
}

bool Round::hasNext() const
{TRM;
    // should be called before goToNextRoundStage
    return (m_currentRoundStage != RoundStageEnum::RoundSummary);
}

void Round::goToNext()
{TRM;
    matchEnd();

    m_currentRoundStage = static_cast<RoundStageEnum>(m_currentRoundStage+1);
    emit this->currentRoundStageChanged();

    matchStart();
}

void Round::assignExampleData()
{TRM;
    /// for all matches
    for(auto &matchPtr : m_matches)
        matchPtr->assignExampleData();
}

void Round::matchStart()
{TRM;
    for(auto &match : m_matches)
        match->onStart();
}

void Round::matchEnd()
{TRM;
    for(auto &match : m_matches)
        match->onEnd();
}

RoundStageEnum Round::getCurrentRoundStage() const
{
    return m_currentRoundStage;
}

QString Round::getCurrentName() const
{TRM;
    return EnumConvert::RoundStageToQString(m_currentRoundStage);
}

QString Round::getNextName() const
{TRM;
    return EnumConvert::RoundStageToQString(
        static_cast<RoundStageEnum>(m_currentRoundStage +1));
}

MatchPtrVectorQml Round::getMatchesQml() const
{TRM;
    MatchPtrVectorQml retVec;
    retVec.reserve(m_matches.size());
    for(const auto &matchPtr : m_matches)
        retVec.append(matchPtr.data());
    return retVec;
}

void Round::setArrangement(const IntPairs &arrangement)
{TRM;
    m_arrangement = arrangement;
    // D(QAPF("set arrangement for %p Round:", this))
    // for(const auto &pair : m_arrangement)
    // {
    //     D(QAPF("%d %d", pair.first, pair.second))
    // }
}
