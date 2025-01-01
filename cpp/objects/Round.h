#ifndef ROUND_H
#define ROUND_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Match.h"
#include "cpp/enums/RoundStageEnum.h"
#include "cpp/objects/Team.h"
#include "cpp/DebugConstraints.h"

#define SERL_CURRENT_ROUND_STAGE_KEY "current round stage"
#define SERL_ARRANGEMENT_KEY "arrangement"
#define SERL_ARRANGEMENT_MATCH_FIRST_KEY "first"
#define SERL_ARRANGEMENT_MATCH_SECOND_KEY "second"
#define SERL_MATCHES_KEY "matches"

typedef QVector<QPair<int, int>> IntPairs;

class Round : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int currentRoundStage READ getCurrentRoundStage NOTIFY currentRoundStageChanged FINAL)
    Q_PROPERTY(MatchPtrVectorQml matches READ getMatchesQml NOTIFY matchesChanged FINAL)

public:
    explicit Round(TeamPtrList &teams, QObject *parent = nullptr);
    ~Round();

    void initMatches();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jRound) override;
    void deserializeMatches(const QJsonObject &jRound);

    void clear(bool emitting = true);

public:
    bool verify(QString &message) const;
    bool hasNext() const;
    void goToNext();

    void assignExampleData();

public:
    /// GETTERS
    RoundStageEnum getCurrentRoundStage() const;

    /// QML GETTERS
    MatchPtrVectorQml getMatchesQml() const;

    /// SETTERS
    void setArrangement(const IntPairs &arrangement);

signals:
    void currentRoundStageChanged();
    void matchesChanged();

private:
    RoundStageEnum m_currentRoundStage;
    IntPairs m_arrangement; /// const list, set while creating object by setter
    MatchPtrList m_matches; /// const list, created while creating object by initMatches (before setting arrangement)
    TeamPtrList &m_teams;
};

typedef QSharedPointer<Round> RoundPtr;
typedef QVector<RoundPtr> RoundPtrVector;
typedef QVector<Round *> QmlRoundPtrVector;

#endif // ROUND_H
