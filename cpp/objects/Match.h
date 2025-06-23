#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>

#include "Serializable.h"
#include "objects/Team.h"
#include "enums/RoundStageEnum.h"
#include "objects/MatchTypeBase.h"

#define SERL_MATCH_TEAM_LEFT_NAME_KEY "team left name"
#define SERL_MATCH_TEAM_RIGHT_NAME_KEY "team right name"
#define SERL_MATCH_TYPES_KEY "match types"
#define SERL_MATCH_TYPE_SINGLES_KEY "singles"
#define SERL_MATCH_TYPE_DOUBLES_KEY "doubles"
#define SERL_MATCH_TYPE_TRIPLES_KEY "triples"

typedef const RoundStageEnum *const RoundStageEnumRPtr;

class Match : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(Team *teamLeft READ getTeamLeft CONSTANT FINAL)
    Q_PROPERTY(Team *teamRight READ getTeamRight CONSTANT FINAL)
    Q_PROPERTY(MatchTypeBase *currentMatchType READ getCurrentMatchType NOTIFY currentRoundStageChanged FINAL)

public:
    explicit Match(RoundStageEnumRPtr roundStageRef, QObject *parent = nullptr);
    ~Match();

    void onStart();
    void onEnd();

    void initMatchesTypes();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jMatch) override;

    void clear(bool emitting = true);

private:
    QString serializeTeam(const TeamWPtr &teamWPtr) const;
    QJsonObject serializeMatchType(int matchTypeIndex) const;
    void deserializeMatchTypes(const QJsonObject &jMatch);
    void deserializeMatchType(const QJsonObject &jMatchTypes, int index);

public:
    bool verify(QString &message) const;

    void assignExampleData();

public:
    /// GETTERS
    Team *getTeamLeft() const;
    Team *getTeamRight() const;
    MatchTypeBase *getCurrentMatchType() const;

    /// SETTERS
    void setTeamLeft(const TeamPtr &team);
    void setTeamRight(const TeamPtr &team);

signals:
    void currentRoundStageChanged();

private:
    /// holds left team used in this match
    TeamPtr m_teamLeft; /// const assigned while creation of object
    /// holds right team used in this match
    TeamPtr m_teamRight; /// const assigned while creation of object

    /// holds constant reference to current round stage from Round
    /// is used to extract information what type that match is, for example:
    /// SinglesSelection, SinglesMatch -> Singles
    /// DoublesSelection, DoublesMatch -> Doubles
    /// TriplesSelection, TriplesMatch -> Triples
    /// RoundSummary is not used
    RoundStageEnumRPtr m_currentRoundStage;

    /// stores 3 MatchTypeBase types - class is abstract and holds:
    /// MatchSingles, MatchDoubles, MatchTriples objects
    MatchTypeBasePtrVector m_matchTypes;
};

typedef QSharedPointer<Match> MatchPtr;
typedef QList<MatchPtr> MatchPtrList;
typedef QVector<Match*> MatchPtrVectorQml;

#endif // MATCH_H
