#ifndef GROUPSELECTION_H
#define GROUPSELECTION_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QRandomGenerator>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"

#define SERL_GROUP_SELECTION_GROUPS_COUNT_KEY "groups count"
#define SERL_GROUP_SELECTION_MIN_PLAYERS_IN_GROUP_KEY "min players in group"
#define SERL_GROUP_SELECTION_MAX_PLAYERS_IN_GROUP_KEY "max players in group"
#define SERL_GROUP_SELECTION_PLAYER_SELECTIONS_KEY "player selections"
#define SERL_GROUP_SELECTION_TEAM_NAME_KEY "team name"

// const int m_groupsCount;
// const int m_minPlayersInGroup;
// const int m_maxPlayersInGroup;
// QList<int> m_playerSelections;
// TeamWPtr m_team;

typedef QList<int> IntList;

class GroupSelection : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int groupsCount READ getGroupsCount CONSTANT FINAL)
    Q_PROPERTY(QStringList comboBoxModel READ getComboBoxModel CONSTANT FINAL)
    Q_PROPERTY(const IntList &playerSelections READ getPlayerSelections NOTIFY playerSelectionsChanged FINAL)
    Q_PROPERTY(const Team *team READ getTeamQml NOTIFY teamChanged FINAL)

public:
    explicit GroupSelection(int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent = nullptr);
    ~GroupSelection();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupSelection) override;

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
    QStringList getComboBoxModel() const;

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
    TeamPtr m_team;

    static constexpr int defaultSelectionValue = -1;
};

typedef QSharedPointer<GroupSelection> GroupSelectionPtr;
typedef QList<GroupSelectionPtr> GroupSelectionPtrList;
typedef QVector<GroupSelection *> QmlGroupSelectionPtrVector;

#endif // GROUPSELECTION_H
