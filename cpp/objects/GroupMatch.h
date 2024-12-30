#ifndef GROUPMATCH_H
#define GROUPMATCH_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"
#include "cpp/objects/Player.h"

typedef QList<QList<Player*>> ListOfPlayersListQml;

class GroupMatch : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int groupsCount READ getGroupsCount NOTIFY groupsCountChanged FINAL)
    Q_PROPERTY(int defaultPlayersCountInGroup READ getDefaultPlayersCountInGroup NOTIFY defaultPlayersCountInGroupChanged FINAL)
    Q_PROPERTY(ListOfPlayersListQml groupsOfPlayers READ getGroupsOfPlayers NOTIFY groupsOfPlayersChanged FINAL)
    Q_PROPERTY(QList<int> matchPoints READ getMatchPoints NOTIFY matchPointsChanged FINAL)
    Q_PROPERTY(Team *team READ getTeamQml NOTIFY teamChanged FINAL)

public:
    explicit GroupMatch(QObject *parent = nullptr);
    ~GroupMatch();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupMatch) override;

    void clear(bool emitting = true);

public slots:
    void setGroupPoints(int group, int points);

public:
    bool verify(QString &message);
    void assignExampleData();

public:
    int getGroupsCount() const;
    int getDefaultPlayersCountInGroup() const;
    ListOfPlayersListQml getGroupsOfPlayers() const;
    const QList<int> &getMatchPoints() const;
    Team *getTeamQml() const;

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
    QList<int> m_matchPoints;
    TeamWPtr m_team;
};

typedef QSharedPointer<GroupMatch> GroupMatchPtr;
typedef QList<GroupMatchPtr> GroupMatchPtrList;
typedef QVector<GroupMatch *> QmlGroupMatchPtrVector;

#endif // GROUPMATCH_H
