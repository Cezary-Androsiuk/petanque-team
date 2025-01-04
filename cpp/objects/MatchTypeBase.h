#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QRandomGenerator>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/GroupSelection.h"
#include "cpp/objects/GroupMatch.h"
#include "cpp/objects/Team.h"

#define SERL_MATCH_TYPE_TEAM_LEFT_NAME_KEY "team left name"
#define SERL_MATCH_TYPE_TEAM_RIGHT_NAME_KEY "team right name"
#define SERL_GROUPS_COUNT_KEY "groups count"
#define SERL_MIN_PLAYERS_IN_GROUP_KEY "min players in group"
#define SERL_MAX_PLAYERS_IN_GROUP_KEY "max players in group"
#define SERL_GROUP_SELECTION_LEFT_KEY "group selection left"
#define SERL_GROUP_SELECTION_RIGHT_KEY "group selection right"
#define SERL_GROUP_MATCH_LEFT_KEY "group match left"
#define SERL_GROUP_MATCH_RIGHT_KEY "group match right"

typedef const TeamWPtr &cTeamWPtr;
typedef QList<int> IntList;

class MatchTypeBase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(Team *teamLeft READ getTeamLeftQml CONSTANT FINAL)
    Q_PROPERTY(Team *teamRight READ getTeamRightQml CONSTANT FINAL)
    Q_PROPERTY(GroupSelection *selectionLeft READ getSelectionLeft NOTIFY selectionChanged FINAL)
    Q_PROPERTY(GroupSelection *selectionRight READ getSelectionRight NOTIFY selectionChanged FINAL)
    Q_PROPERTY(GroupMatch *matchLeft READ getMatchLeft NOTIFY matchChanged FINAL)
    Q_PROPERTY(GroupMatch *matchRight READ getMatchRight NOTIFY matchChanged FINAL)

public:
    explicit MatchTypeBase(
        TeamPtr teamL, TeamPtr teamR,
        int groupsCount, int minPlayersInGroup, int maxPlayersInGroup,
        QObject *parent = nullptr);
    virtual ~MatchTypeBase();

    void onStart();
    void onEnd();

public slots:
    void initSelection(); /// call on complition qml selection
    void initMatch(); /// call on complition qml match

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jMatchTypeBase) override;

    void clear(bool emitting = true);

private:
    QString serializeTeam(cTeamWPtr wteam) const;

public slots:
    bool verifySelection(QString &message);
    bool verifyMatch(QString &message);

private:
    QList<PlayerPtrList> makeGroupsOfPlayersList(const PlayerPtrList &wteam, const IntList &selection) const;

public:
    void assignSelectionExampleData();
    void assignMatchExampleData();

private:
    static void generateTwoRandomValues1(int &v1, int &v2, int max);
    static void generateTwoRandomValues2(int &v1, int &v2, int max);
    static void generateTwoRandomValues3(int &v1, int &v2, int max);

public:
    /// GETTERS
    Team *getTeamLeftQml() const;
    Team *getTeamRightQml() const;
    GroupSelection *getSelectionLeft() const;
    GroupSelection *getSelectionRight() const;
    GroupMatch *getMatchLeft() const;
    GroupMatch *getMatchRight() const;

    /// SETTERS


signals:
    void selectionChanged();
    void matchChanged();

private:
    const int m_groupsCount;
    const int m_minPlayersInGroup;
    const int m_maxPlayersInGroup;
    TeamPtr m_teamLeft;
    TeamPtr m_teamRight;

    bool m_selectionInitialized;
    GroupSelectionPtr m_groupSelectionLeft;
    GroupSelectionPtr m_groupSelectionRight;
    bool m_matchInitialized;
    GroupMatchPtr m_groupMatchLeft;
    GroupMatchPtr m_groupMatchRight;
};

typedef QSharedPointer<MatchTypeBase> MatchTypeBasePtr;
typedef QVector<MatchTypeBasePtr> MatchTypeBasePtrVector;
typedef QVector<MatchTypeBase *> QmlMatchTypeBasePtrVector;


#endif // MATCHTYPEBASE_H
