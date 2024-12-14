#ifndef ROUND_H
#define ROUND_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/objects/Match.h"

class Round : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Round(QObject *parent = nullptr);

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

signals:

private:
    MatchPtrList m_matches;
};

typedef QSharedPointer<Round> RoundPtr;
typedef QVector<RoundPtr> RoundPtrVector;
typedef QVector<Round *> QmlRoundPtrVector;

#endif // ROUND_H
