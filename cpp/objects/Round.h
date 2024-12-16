#ifndef ROUND_H
#define ROUND_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/enums/RoundStageEnum.h"
#include "cpp/objects/MatchTypeBase.h"

typedef QVector<QPair<int, int>> IntPairs;

class Round : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int currentRoundStage READ getCurrentRoundStage NOTIFY currentRoundStageChanged FINAL)

public:
    explicit Round(QObject *parent = nullptr);
    ~Round();

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
    RoundStageEnum getCurrentRoundStage() const;

    /// SETTERS
    void setArrangement(const IntPairs &arrangement);

signals:
    void currentRoundStageChanged();

private:
    IntPairs m_arrangement;
    RoundStageEnum m_currentRoundStage;
    const MatchTypeBasePtrVector m_matchTypes;
};

typedef QSharedPointer<Round> RoundPtr;
typedef QVector<RoundPtr> RoundPtrVector;
typedef QVector<Round *> QmlRoundPtrVector;

#endif // ROUND_H
