#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"
#include "cpp/objects/Phase.h"

#include "cpp/enums/PhaseEnum.h"
#include "cpp/enums/StageEnum.h"


/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_EVENT_NAME_KEY     "name"
#define SERL_CURRENT_PHASE_KEY  "current phase"
#define SERL_CURRENT_STAGE_KEY  "current stage"
#define SERL_PHASE_FIRST_KEY    "phase first"
#define SERL_PHASE_SECOND_KEY   "phase second"

class Event : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(PhaseEnum currentPhase READ getCurrentPhase NOTIFY currentPhaseChanged FINAL)
    Q_PROPERTY(StageEnum currentStage READ getCurrentStage NOTIFY currentStageChanged FINAL)
    Q_PROPERTY(QmlPhasePtrVector phases READ getPhasesQml NOTIFY phasesChanged FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();


    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &eventJson) override;

    void clear(bool emitting = true);

public slots:
    void goToNextStage();
    void goToPrevStage();

private:
    void initialize();
    void createPhases();

public:
    /// GETTERS
    QString getName() const;
    PhaseEnum getCurrentPhase() const;
    StageEnum getCurrentStage() const;
    PhasePtrVector getPhases() const;

    /// QML LIST GETTERS
    QmlPhasePtrVector getPhasesQml() const;

    /// SETTERS
    void setName(const QString &name);
    
signals:
    /// VARIABLE SIGNALS
    void nameChanged();
    void currentPhaseChanged();
    void currentStageChanged();
    void phasesChanged();

private:
    QString m_name;
    PhaseEnum m_currentPhase;
    StageEnum m_currentStage;
    PhasePtrVector m_phases;


};

#endif // EVENT_H
