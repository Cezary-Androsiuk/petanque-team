#ifndef ROUND_H
#define ROUND_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/MatchTypeBase.h"

typedef QVector<QPair<int, int>> IntPairs;

class Round : public QObject, public Serializable
{
    Q_OBJECT
public:
    enum RoundStage{
        SingielsSelection = 0,
        SingielsMatch,
        DubletsSelection,
        DubletsMatch,
        TripletsSelection,
        TripletsMatch,
        RoundSummary,
    };

    explicit Round(QObject *parent = nullptr);
    ~Round();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

public:
    bool verify(QString &message) const;
    bool hasNextRoundStage() const;
    void goToNextRoundStage();

signals:

private:
    IntPairs m_arrangement;
    RoundStage m_currentRoundStage;
    const MatchTypeBasePtrVector m_matchTypes;
};

typedef QSharedPointer<Round> RoundPtr;
typedef QVector<RoundPtr> RoundPtrVector;
typedef QVector<Round *> QmlRoundPtrVector;

#endif // ROUND_H
