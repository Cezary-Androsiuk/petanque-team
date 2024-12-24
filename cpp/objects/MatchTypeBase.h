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

class MatchTypeBase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit MatchTypeBase(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    virtual ~MatchTypeBase();

    void initSelection();
    void initMatch();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

public:
    bool verifySelection(QString &message);
    bool verifyMatch(QString &message);

signals:

private:
    GroupSelectionPtr m_groupSelectionLeft;
    GroupSelectionPtr m_groupSelectionRight;
    GroupMatchPtr m_groupMatchLeft;
    GroupMatchPtr m_groupMatchRight;
};

typedef QSharedPointer<MatchTypeBase> MatchTypeBasePtr;
typedef QVector<MatchTypeBasePtr> MatchTypeBasePtrVector;
typedef QVector<MatchTypeBase *> QmlMatchTypeBasePtrVector;


#endif // MATCHTYPEBASE_H
