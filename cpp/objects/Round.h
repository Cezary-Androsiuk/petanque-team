#ifndef ROUND_H
#define ROUND_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Match.h"
#include "cpp/objects/Team.h"
#include "cpp/DebugConstraints.h"

typedef QVector<QPair<int, int>> IntPairs;

class Round : public QObject, public Serializable
{
    Q_OBJECT

public:
    explicit Round(QObject *parent = nullptr);
    ~Round();

    void initMatches();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

public:
    bool verify(QString &message) const;
    bool hasNext() const;
    void goToNext();

public:
    /// GETTERS

    /// SETTERS
    void setArrangement(const IntPairs &arrangement);

signals:
    void currentRoundStageChanged();

private:
    IntPairs m_arrangement;
    MatchPtrList m_matches;
};

typedef QSharedPointer<Round> RoundPtr;
typedef QVector<RoundPtr> RoundPtrVector;
typedef QVector<Round *> QmlRoundPtrVector;

#endif // ROUND_H
