#ifndef ROUND_H
#define ROUND_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "Serializable.h"
#include "objects/Match.h"
#include "enums/RoundStageEnum.h"
#include "objects/Team.h"

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

    void onStart();
    void onEnd();

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

private:
    void matchStart();
    void matchEnd();

public:
    /// GETTERS
    RoundStageEnum getCurrentRoundStage() const;

    QString getCurrentName() const;
    QString getNextName() const;

    /// QML GETTERS
    MatchPtrVectorQml getMatchesQml() const;

    /// SETTERS
    void setArrangement(const IntPairs &arrangement);

signals:
    void currentRoundStageChanged();
    void matchesChanged();

private:
    /// holds current round stage (SinglesSelection, SinglesMatch, ..., RoundSummary)
    RoundStageEnum m_currentRoundStage;

    /// arrangement - which team will fight with which
    /// 4 pairs when phase is First, and 2 pairs in each when phase is Second
    IntPairs m_arrangement; /// const list, set while creating object by setter

    /// holds list of matches (count coresponds to m_arrangement size)
    MatchPtrList m_matches; /// const list, created while creating object by initMatches (before setting arrangement)

    /// reference teams list from subphases - used to pass reference single teams to matches
    TeamPtrList &m_teams;
};

typedef QSharedPointer<Round> RoundPtr;
typedef QVector<RoundPtr> RoundPtrVector;
typedef QVector<Round *> QmlRoundPtrVector;

#endif // ROUND_H
