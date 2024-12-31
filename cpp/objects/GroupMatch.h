#ifndef GROUPMATCH_H
#define GROUPMATCH_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"
#include "cpp/objects/Player.h"

#define SERL_GROUP_MATCH_GROUPS_COUNT_KEY "groups count"
#define SERL_GROUP_MATCH_DEFAULT_PLAYERS_COUNT_IN_GROUP_KEY "default players count in group"
#define SERL_GROUP_MATCH_DPLCIG_KEY /**/ SERL_GROUP_MATCH_DEFAULT_PLAYERS_COUNT_IN_GROUP_KEY
#define SERL_GROUP_MATCH_GROUPS_OF_PLAYERS_KEY "groups of players"
#define SERL_GROUP_MATCH_MATCH_POINTS_KEY "match points"
#define SERL_GROUP_MATCH_TEAM_NAME_KEY "team name"

typedef QList<int> IntList;
typedef QVector<QmlPlayerPtrVector> QmlVecOfPlayersVec;

class GroupMatch : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int groupsCount READ getGroupsCount NOTIFY groupsCountChanged FINAL)
    Q_PROPERTY(int defaultPlayersCountInGroup READ getDefaultPlayersCountInGroup NOTIFY defaultPlayersCountInGroupChanged FINAL)
    Q_PROPERTY(QmlVecOfPlayersVec groupsOfPlayers READ getGroupsOfPlayers NOTIFY groupsOfPlayersChanged FINAL)
    Q_PROPERTY(const IntList &matchPoints READ getMatchPoints NOTIFY matchPointsChanged FINAL)
    Q_PROPERTY(const Team *team READ getTeamQml NOTIFY teamChanged FINAL)

public:
    explicit GroupMatch(QObject *parent = nullptr);
    ~GroupMatch();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupMatch) override;

private:
    QJsonArray serializeGroupsOfPlayers() const;

public slots:
    void setGroupPoints(int group, int points);

public:
    bool verify(QString &message);
    void assignExampleData();

public:
    int getGroupsCount() const;
    int getDefaultPlayersCountInGroup() const;
    QmlVecOfPlayersVec getGroupsOfPlayers() const;
    const IntList &getMatchPoints() const;
    const Team *getTeamQml() const;

    void setGroupsCount(int groupsCount);
    void setDefaultPlayersCountInGroup(int defaultPlayersCountInGroup);
    void setGroupsOfPlayers(const QList<PlayerPtrList> &groupsOfPlayers);
    void setMatchPointsSize(int matchPointsSize);
    void setTeam(TeamPtr team);

signals:
    void groupsCountChanged();
    void defaultPlayersCountInGroupChanged();
    void groupsOfPlayersChanged();
    void matchPointsChanged();
    void teamChanged();

private:
    int m_groupsCount;
    int m_defaultPlayersCountInGroup;

    QList<PlayerPtrList> m_groupsOfPlayers;
    IntList m_matchPoints;
    TeamWPtr m_team;
};

typedef QSharedPointer<GroupMatch> GroupMatchPtr;
typedef QList<GroupMatchPtr> GroupMatchPtrList;
typedef QVector<GroupMatch *> QmlGroupMatchPtrVector;

#endif // GROUPMATCH_H
