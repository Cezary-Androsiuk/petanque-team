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
public:
    explicit MatchTypeBase(cTeamWPtr teamL, cTeamWPtr teamR, QObject *parent = nullptr);
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

signals:

private:
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
