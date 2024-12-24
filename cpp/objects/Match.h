#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"
#include "cpp/enums/RoundStageEnum.h"
#include "cpp/objects/MatchTypeBase.h"

#define SERL_TEAM_LEFT_NAME_KEY "team left"
#define SERL_TEAM_RIGHT_NAME_KEY "team right"
#define SERL_MATCH_TYPES_KEY "match types"
#define SERL_MATCH_TYPE_SINGIELS_KEY "singiels"
#define SERL_MATCH_TYPE_DUBLETS_KEY "dublets"
#define SERL_MATCH_TYPE_TRIPLETS_KEY "triplets"

class Match : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(Team *teamLeft READ getTeamLeft CONSTANT FINAL)
    Q_PROPERTY(Team *teamRight READ getTeamRight CONSTANT FINAL)
    Q_PROPERTY(MatchTypeBase *currentMatchType READ getCurrentMatchType NOTIFY currentRoundStageChanged FINAL)

public:
    explicit Match(const RoundStageEnum &roundStageRef, QObject *parent = nullptr);
    ~Match();

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
    TeamWPtr m_teamLeft; /// const assigned while creation of object
    TeamWPtr m_teamRight; /// const assigned while creation of object

    const RoundStageEnum &m_currentRoundStage;
    MatchTypeBasePtrVector m_matchTypes;
};

typedef QSharedPointer<Match> MatchPtr;
typedef QList<MatchPtr> MatchPtrList;
typedef QVector<Match*> MatchPtrVectorQml;

#endif // MATCH_H
