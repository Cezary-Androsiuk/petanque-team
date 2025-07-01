#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QRandomGenerator>

#include "Serializable.h"
#include "objects/GroupSelection.h"
#include "objects/GroupMatch.h"
#include "objects/Team.h"

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

    void onSelectionStart();
    void onSelectionEnd();
    void onMatchStart();
    void onMatchEnd();

public slots:
    /// following methods are called in qml (in selection and match) as well here in onStart methods
    /// i mean that is pain in the ass, maybe i will reiplement it in future
    void initSelection();
    void initMatch();

private:
    void addPoints();
    void addPointsForTeams();
    void addPointsForPlayers();

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
    static void generateTwoRandomValues(int &v1, int &v2, int max);

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
    /// holds information how much groups are in this round stage
    /// Singles = 6
    /// Doubles = 3
    /// Triples = 2
    const int m_groupsCount;

    /// holds min players in the group
    /// Singles = 1
    /// Doubles = 2
    /// Triples = 3
    const int m_minPlayersInGroup;

    /// holds max players in the group
    /// Singles = 1
    /// Doubles = 3
    /// Triples = 4
    const int m_maxPlayersInGroup;

    ///         | groups | min | max |
    /// ==============================
    /// Singles |    6   |  1  |  1  |
    /// Doubles |    3   |  2  |  3  |
    /// Triples |    2   |  3  |  4  |


    /// left team that is used in this match
    TeamPtr m_teamLeft;
    /// right team that is used in this match
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
