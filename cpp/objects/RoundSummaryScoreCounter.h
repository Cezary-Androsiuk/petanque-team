#ifndef ROUNDSUMMARYSCORECOUNTER_H
#define ROUNDSUMMARYSCORECOUNTER_H

#include <QObject>
#include <QQmlParserStatus>

#include "SubPhase.h"
#include "TeamScore.h"

/// Class registered as a QML type and created by QML (inside SubPhase.qml), but
///     only when RoundSummary is about to show
class RoundSummaryScoreCounter : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus) /// allow to override componentComplete
    Q_PROPERTY(SubPhase *subPhasePtr READ getSubPhasePtr WRITE setSubPhasePtr NOTIFY subPhasePtrChanged FINAL)
    Q_PROPERTY(TeamPtrScores teamScores READ getTeamScores NOTIFY teamScoresChanged FINAL)

public:
    explicit RoundSummaryScoreCounter(QObject *parent = nullptr);
    ~RoundSummaryScoreCounter();

    /// called after qml component is completed
    void componentComplete() override;
    /// this method also needs to be overridden, so the class won't be abstract
    void classBegin() override;


    /// GETTERS
    SubPhase *getSubPhasePtr() const;
    TeamPtrScores getTeamScores() const;

    /// SETTERS
    void setSubPhasePtr(SubPhase *subPhasePtr);

signals:
    void subPhasePtrChanged();
    void teamScoresChanged();

private:
    /// Pointer to the subPhase, given by QML while initialization
    SubPhase *m_subPhasePtr;

    /// Objects list for storing scored for each team, and displaying them in QML
    TeamPtrScores m_teamScores;
};

#endif // ROUNDSUMMARYSCORECOUNTER_H
