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
    Q_PROPERTY(QList<PlayerPtrList> groupsOfPlayers READ getGroupsOfPlayers CONSTANT FINAL)
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
    QList<PlayerPtrList> getGroupsOfPlayers() const;

    void setGroupsOfPlayers(const QList<PlayerPtrList> &groupsOfPlayers);

signals:

private:
    QList<PlayerPtrList> m_groupsOfPlayers;
};

typedef QSharedPointer<GroupMatch> GroupMatchPtr;
typedef QList<GroupMatchPtr> GroupMatchPtrList;
typedef QVector<GroupMatch *> QmlGroupMatchPtrVector;

#endif // GROUPMATCH_H
