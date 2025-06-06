#ifndef SUBPHASE_H
#define SUBPHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "Serializable.h"
#include "objects/Round.h"
#include "objects/Team.h"

#define SERL_SUB_PHASE_NAME_KEY "name"
#define SERL_CURRENT_ROUND_INDEX_KEY "current round index"
#define SERL_ROUNDS_KEY "rounds"

typedef QVector<QPair<int, int>> IntPairs;

class SubPhase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int currentRoundIndex READ getCurrentRoundIndex NOTIFY currentRoundIndexChanged FINAL)
    Q_PROPERTY(Round *currentRound READ getCurrentRound NOTIFY currentRoundIndexChanged FINAL)
    Q_PROPERTY(QmlRoundPtrVector rounds READ getRoundsQml NOTIFY roundsChanged FINAL)

public:
    explicit SubPhase(int roundsCount, QObject *parent = nullptr);
    ~SubPhase();

    void onStart();
    void onEnd();

    void initRounds(QJsonArray arrangements);

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jSubPhase) override;
    void deserializeRounds(const QJsonObject &jSubPhase);

    void clear(bool emitting = true);

public:
    bool verify(QString &message) const;
    bool hasNext() const;
    void goToNext();

    void assignExampleData();

private:
    void roundStart();
    void roundEnd();

public:
    /// GETTERS
    QString getName() const;
    int getCurrentRoundIndex() const;
    const RoundPtrVector &getRounds() const;

    QString getCurrentName() const;
    QString getNextName() const;

    /// QML GETTERS
    Round *getCurrentRound() const;
    QmlRoundPtrVector getRoundsQml() const;

    /// SETTERS
    void setName(const QString &name);
    void setTeams(const TeamPtrList &teams);

signals:
    void nameChanged();
    void currentRoundIndexChanged();
    void roundsChanged();
    void teamsChanged();

private:
    QString m_name; /// should be constant - set within initialization by setter
    int m_currentRoundIndex;
    RoundPtrVector m_rounds; /// const list, and created while initialization by initRounds
    TeamPtrList m_teams;
};

typedef QSharedPointer<SubPhase> SubPhasePtr;
typedef QVector<SubPhasePtr> SubPhasePtrVector;
typedef QVector<SubPhase *> QmlSubPhasePtrVector;

#endif // SUBPHASE_H
