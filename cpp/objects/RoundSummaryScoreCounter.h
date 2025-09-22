#ifndef ROUNDSUMMARYSCORECOUNTER_H
#define ROUNDSUMMARYSCORECOUNTER_H

#include <QObject>

#include "SubPhase.h"
#include "TeamScore.h"

class RoundSummaryScoreCounter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SubPhase *subPhasePtr READ getSubPhasePtr WRITE setSubPhasePtr NOTIFY subPhasePtrChanged FINAL)
public:
    explicit RoundSummaryScoreCounter(QObject *parent = nullptr);
    ~RoundSummaryScoreCounter();

    SubPhase *getSubPhasePtr() const;
    void setSubPhasePtr(SubPhase *subPhasePtr);

    QString getData() const;
    void setData(const QString &newData);

signals:
    void subPhasePtrChanged();

    void dataChanged();

public slots:
    void buildRankings();

private:
    SubPhase *m_subPhasePtr;

    TeamScores m_teamScores;

    QString m_data;
    Q_PROPERTY(QString data READ getData WRITE setData NOTIFY dataChanged FINAL)
};

#endif // ROUNDSUMMARYSCORECOUNTER_H
