#ifndef GROUPMATCH_H
#define GROUPMATCH_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Player.h"

class GroupMatch : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int groupsCount READ getGroupsCount NOTIFY groupsCountChanged FINAL)
    Q_PROPERTY(int defaultPlayersCountInGroup READ getDefaultPlayersCountInGroup NOTIFY defaultPlayersCountInGroupChanged FINAL)
    Q_PROPERTY(QList<PlayerPtrList> groupsOfPlayers READ getGroupsOfPlayers NOTIFY groupsOfPlayersChanged FINAL)

public:
    explicit GroupMatch(QObject *parent = nullptr);
    ~GroupMatch();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupMatch) override;

    void clear(bool emitting = true);

public:
    bool verify(QString &message);
    void assignExampleData();

public:
    int getGroupsCount() const;
    int getDefaultPlayersCountInGroup() const;
    const QList<PlayerPtrList> &getGroupsOfPlayers() const;

    void setGroupsCount(int groupsCount);
    void setDefaultPlayersCountInGroup(int defaultPlayersCountInGroup);
    void setGroupsOfPlayers(const QList<PlayerPtrList> &groupsOfPlayers);

signals:
    void groupsCountChanged();
    void defaultPlayersCountInGroupChanged();
    void groupsOfPlayersChanged();

private:
    int m_groupsCount;
    int m_defaultPlayersCountInGroup;

    QList<PlayerPtrList> m_groupsOfPlayers;
};

typedef QSharedPointer<GroupMatch> GroupMatchPtr;
typedef QList<GroupMatchPtr> GroupMatchPtrList;
typedef QVector<GroupMatch *> QmlGroupMatchPtrVector;

#endif // GROUPMATCH_H
