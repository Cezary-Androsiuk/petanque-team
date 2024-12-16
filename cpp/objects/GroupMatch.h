#ifndef GROUPMATCH_H
#define GROUPMATCH_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class GroupMatch : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit GroupMatch(QObject *parent = nullptr);
    ~GroupMatch();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

signals:

private:

};

typedef QSharedPointer<GroupMatch> GroupMatchPtr;
typedef QList<GroupMatchPtr> GroupMatchPtrList;
typedef QVector<GroupMatch *> QmlGroupMatchPtrVector;

#endif // GROUPMATCH_H
