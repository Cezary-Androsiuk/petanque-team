#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/GroupMatch.h"

class MatchTypeBase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit MatchTypeBase(QObject *parent = nullptr);
    virtual ~MatchTypeBase();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);
public:
    bool verifySelection(QString &message);
    bool verifyMatch(QString &message);

signals:

private:
    GroupMatchPtrList m_groupMatches;
};

typedef QSharedPointer<MatchTypeBase> MatchTypeBasePtr;
typedef QVector<MatchTypeBasePtr> MatchTypeBasePtrVector;
typedef QVector<MatchTypeBase *> QmlMatchTypeBasePtrVector;


#endif // MATCHTYPEBASE_H
