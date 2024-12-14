#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class MatchTypeBase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit MatchTypeBase(QObject *parent = nullptr);
    virtual ~MatchTypeBase() = default;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

signals:
};

typedef QSharedPointer<MatchTypeBase> MatchTypeBasePtr;
typedef QList<MatchTypeBasePtr> MatchTypeBasePtrList;
typedef QVector<MatchTypeBase *> QmlMatchTypeBasePtrVector;


#endif // MATCHTYPEBASE_H
