#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "Serializable.h"
#include "objects/Team.h"
#include "objects/Phase.h"

#include "enums/PhaseEnum.h"
#include "enums/StageEnum.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_EVENT_NAME_KEY     "name"
#define SERL_CURRENT_PHASE_KEY  "current phase"
#define SERL_CURRENT_STAGE_KEY  "current stage"
#define SERL_PHASE_FIRST_KEY    "phase first"
#define SERL_PHASE_SECOND_KEY   "phase second"
#define SERL_TEAMS_KEY          "teams"

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

public:
    /// SERIALIZABLE STUFF
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jEvent) override;

    /// SUPPORT STUFF
    void clear(bool emitting = true);

public slots:
    /// STAGE STUFF
    void goToNextStage();
    void goToPrevStage(); // ?
    void startFinishStage(); // ?

    /// PHASE STUFF
    bool hasNextPhase() const;
    void startFirstPhase(); /// executed in qml, Event.qml
    void startSecondPhase(); /// executed in qml, Phase.qml

    /// TEAM STUFF
    void createDetachedTeam();
    void deleteDetachedTeam();
    void validateDetachedTeam();
    void addDetachedTeam();

    void deleteTeam(int index);

    /// VERIFICATION
    void validateEvent();

    /// EXAMPLE
    void assignExampleData();

private:
    void firstPhaseStart();
    void secondPhaseEnd();
    void createListForFirstPhase(TeamPtrList &teams1) const;
    void createListForSecondPhase(TeamPtrList &teams2a, TeamPtrList &teams2b) const;

public:
    /// GETTERS
    const QString &getName() const;
    PhaseEnum getCurrentPhase() const;
    StageEnum getCurrentStage() const;

    const PhasePtrVector &getPhases() const;

    const TeamPtr &getDetachedTeam() const;
    const TeamPtrList &getTeams() const;

    Q_INVOKABLE QString getConfirmNextPopupTextFrom() const;
    Q_INVOKABLE QString getConfirmNextPopupTextTo() const;

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
    /// Event details
    QString m_name;

    /// Current Stage - None, Configure, Play, Finish
    StageEnum m_currentStage;

    /// Current Phase - First or Second (used in Play stage)
    PhaseEnum m_currentPhase;
    /// Phases - First Phase and the Second one (both are stored in memory)
    PhasePtrVector m_phases;

    /// Team Temporary Handler
    TeamPtr m_detachedTeam;
    /// Teams in Event
    TeamPtrList m_teams;
};

#endif // EVENT_H
