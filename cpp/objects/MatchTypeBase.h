#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/GroupSelection.h"
#include "cpp/objects/GroupMatch.h"
#include "cpp/objects/Team.h"

typedef const TeamWPtr &cTeamWPtr;

class MatchTypeBase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(GroupSelection *selectionLeft READ getSelectionLeft NOTIFY selectionChanged FINAL)
    Q_PROPERTY(GroupSelection *selectionRight READ getSelectionRight NOTIFY selectionChanged FINAL)
public:
    explicit MatchTypeBase(
        cTeamWPtr teamL, cTeamWPtr teamR,
        int groupsCount, int minPlayersInGroup, int maxPlayersInGroup,
        QObject *parent = nullptr);
    virtual ~MatchTypeBase();

public slots:
    void initSelection(); /// call on complition qml selection
    void initMatch(); /// call on complition qml match

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

public slots:
    bool verifySelection(QString &message);
    bool verifyMatch(QString &message);

public:
    void assignSelectionExampleData();
    void assignMatchExampleData();

public:
    /// GETTERS
    // Team *getTeamLeft() const;
    // Team *getTeamRight() const;
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
    cTeamWPtr m_teamLeft;
    cTeamWPtr m_teamRight;

    GroupSelectionPtr m_groupSelectionLeft;
    GroupSelectionPtr m_groupSelectionRight;
    GroupMatchPtr m_groupMatchLeft;
    GroupMatchPtr m_groupMatchRight;
};

typedef QSharedPointer<MatchTypeBase> MatchTypeBasePtr;
typedef QVector<MatchTypeBasePtr> MatchTypeBasePtrVector;
typedef QVector<MatchTypeBase *> QmlMatchTypeBasePtrVector;


#endif // MATCHTYPEBASE_H
