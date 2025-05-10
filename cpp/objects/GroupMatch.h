#ifndef GROUPMATCH_H
#define GROUPMATCH_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "Serializable.h"
#include "objects/Team.h"
#include "objects/Player.h"

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
    Q_PROPERTY(QmlVecOfPlayersVec groupsOfPlayers READ getGroupsOfPlayersQml NOTIFY groupsOfPlayersChanged FINAL)
    Q_PROPERTY(const IntList &matchPoints READ getMatchPoints NOTIFY matchPointsChanged FINAL)
    Q_PROPERTY(const Team *team READ getTeamQml NOTIFY teamChanged FINAL)
    Q_PROPERTY(int maxPointsInMatch READ getMaxPointsInMatch CONSTANT FINAL)

public:
    explicit GroupMatch(QObject *parent = nullptr);
    ~GroupMatch();

    void onStart();
    void onEnd();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupMatch) override;

private:
    QJsonArray serializeGroupsOfPlayers() const;

public slots:
    void setGroupPoints(int group, int points);

public:
    // bool verify(QString &message); // left and right GroupMatch need to be verified together
    void assignExampleData(const IntList &data);

public:
    int getGroupsCount() const;
    int getDefaultPlayersCountInGroup() const;
    const QList<PlayerPtrList> &getGroupsOfPlayers() const;
    QmlVecOfPlayersVec getGroupsOfPlayersQml() const;
    const IntList &getMatchPoints() const;
    const Team *getTeamQml() const;
    int getMaxPointsInMatch() const;

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
    TeamPtr m_team;

    int m_maxPointsInMatch;
};

typedef QSharedPointer<GroupMatch> GroupMatchPtr;
typedef QList<GroupMatchPtr> GroupMatchPtrList;
typedef QVector<GroupMatch *> QmlGroupMatchPtrVector;

#endif // GROUPMATCH_H
