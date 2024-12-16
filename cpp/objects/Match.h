#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"
#include "cpp/enums/RoundStageEnum.h"
#include "cpp/objects/MatchTypeBase.h"

class Match : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int currentRoundStage READ getCurrentRoundStage NOTIFY currentRoundStageChanged FINAL)

public:
    explicit Match(QObject *parent = nullptr);
    ~Match();

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
    void setTeamLeft(const TeamPtr &team);
    void setTeamRight(const TeamPtr &team);

signals:
    void currentRoundStageChanged();

private:
    TeamWPtr m_teamLeft;
    TeamWPtr m_teamRight;

    RoundStageEnum m_currentRoundStage;
    const MatchTypeBasePtrVector m_matchTypes;
};

typedef QSharedPointer<Match> MatchPtr;
typedef QList<MatchPtr> MatchPtrList;
typedef QVector<Match*> MatchPtrVectorQml;

#endif // MATCH_H
