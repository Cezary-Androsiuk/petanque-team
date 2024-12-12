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
    Q_PROPERTY(Team *detachedTeam READ getDetachedTeamQml NOTIFY detachedTeamChanged FINAL)
    Q_PROPERTY(QmlTeamPtrVector teams READ getTeamsQml NOTIFY teamsChanged FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();

private:
    /// INIT STUFF
    void initialize();
    void createPhases();

public:
    /// SERIALIZABLE STUFF
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &eventJson) override;

    /// SUPPORT STUFF
    void clear(bool emitting = true);

public slots:
    /// STAGE STUFF
    void goToNextStage();
    void goToPrevStage();

    /// PHASE STUFF
    void initFirstPhase();
    void initSecondPhase();

    /// TEAM STUFF
    void createDetachedTeam();
    void deleteDetachedTeam();
    void validateDetachedTeam();
    void addDetachedTeam();

    void deleteTeam(int index);

    /// VERIFICATION
    void validateEvent();

    /// EXAMPLE
    void createExampleTeams();

public:
    /// GETTERS
    const QString &getName() const;
    PhaseEnum getCurrentPhase() const;
    StageEnum getCurrentStage() const;

    const PhasePtrVector &getPhases() const;

    const TeamPtr &getDetachedTeam() const;
    const TeamPtrList &getTeams() const;

    /// QML LIST GETTERS
    QmlPhasePtrVector getPhasesQml() const;

    Team *getDetachedTeamQml() const;
    QmlTeamPtrVector getTeamsQml() const;

    /// SETTERS
    void setName(const QString &name);
    
signals:
    /// VARIABLE SIGNALS
    void nameChanged();
    void currentPhaseChanged();
    void currentStageChanged();

    void phasesChanged();

    void teamsChanged();
    void detachedTeamChanged();

    /// VERIFICATION SIGNALS
    void eventValid();
    void eventValidationFailed(QString message);

    /// TEAMS SIGNALS
    void detachedTeamIsValid();
    void detachedTeamValidationFailed(QString message);

private:
    QString m_name;

    PhaseEnum m_currentPhase;
    StageEnum m_currentStage;

    PhasePtrVector m_phases;

    TeamPtr m_detachedTeam;
    TeamPtrList m_teams;
};

#endif // EVENT_H
