#ifndef GROUPSELECTION_H
#define GROUPSELECTION_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"

typedef QList<int> IntList;

class GroupSelection : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int groupsCount READ getGroupsCount CONSTANT FINAL)
    Q_PROPERTY(const IntList &playerSelections READ getPlayerSelections NOTIFY playerSelectionsChanged FINAL)
    Q_PROPERTY(const Team *team READ getTeamQml NOTIFY teamChanged FINAL)

public:
    explicit GroupSelection(int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent = nullptr);
    ~GroupSelection();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupSelection) override;

    void clear(bool emitting = true);

public:
    bool verify(QString &message);
    void setSelectionSize(qsizetype size);
    void assignExampleData();

public slots:
    void setPlayerGroup(int playerIndex, int groupIndex);

public:
    /// GETTERS
    int getGroupsCount() const;
    const IntList &getPlayerSelections() const;
    const Team *getTeamQml() const;

    /// SETTERS
    void setTeam(TeamPtr team);

signals:
    void playerSelectionsChanged();
    void teamChanged();

private:
    const int m_groupsCount;
    const int m_minPlayersInGroup;
    const int m_maxPlayersInGroup;
    QList<int> m_playerSelections;
    TeamWPtr m_team;

    static constexpr int defaultSelectionValue = -1;
};

typedef QSharedPointer<GroupSelection> GroupSelectionPtr;
typedef QList<GroupSelectionPtr> GroupSelectionPtrList;
typedef QVector<GroupSelection *> QmlGroupSelectionPtrVector;

#endif // GROUPSELECTION_H
