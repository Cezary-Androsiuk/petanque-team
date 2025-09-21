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
#define SERL_EVENT_DETAILS_KEY                  "event details"
#define SERL_EVENT_NAME_KEY                     "event name"
#define SERL_EVENT_FIRST_PHASE_DATE_KEY         "event first phase date"
#define SERL_EVENT_SECOND_PHASE_DATE_KEY        "event second phase date"
#define SERL_EVENT_COMPETITION_ORGANIZER_KEY    "event competition organizer"
#define SERL_EVENT_FIRST_PHASE_PLACE_KEY        "event first phase place"
#define SERL_EVENT_SECOND_PHASE_PLACE_KEY       "event second phase place"
#define SERL_EVENT_UNION_DELEGATE_KEY           "event union delegate"
#define SERL_EVENT_JUDGES_KEY                   "event judges"

#define SERL_CURRENT_PHASE_KEY  "current phase"
#define SERL_CURRENT_STAGE_KEY  "current stage"
#define SERL_PHASE_FIRST_KEY    "phase first"
#define SERL_PHASE_SECOND_KEY   "phase second"
#define SERL_TEAMS_KEY          "teams"

class Event : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name                 READ getName                    WRITE setName                   NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString firstPhaseDate       READ getFirstPhaseDate          WRITE setFirstPhaseDate         NOTIFY firstPhaseDateChanged FINAL)
    Q_PROPERTY(QString secondPhaseDate      READ getSecondPhaseDate         WRITE setSecondPhaseDate        NOTIFY secondPhaseDateChanged FINAL)
    Q_PROPERTY(QString competitionOrganizer READ getCompetitionOrganizer    WRITE setCompetitionOrganizer   NOTIFY competitionOrganizerChanged FINAL)
    Q_PROPERTY(QString firstPhasePlace      READ getFirstPhasePlace         WRITE setFirstPhasePlace        NOTIFY firstPhasePlaceChanged FINAL)
    Q_PROPERTY(QString secondPhasePlace     READ getSecondPhasePlace        WRITE setSecondPhasePlace       NOTIFY secondPhasePlaceChanged FINAL)
    Q_PROPERTY(QStringList judges           READ getJudges                  WRITE setJudges                 NOTIFY judgesChanged FINAL)
    Q_PROPERTY(QString unionDelegate        READ getUnionDelegate           WRITE setUnionDelegate          NOTIFY unionDelegateChanged FINAL)

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
    bool validateEventDetails();

    /// EXAMPLE
    void assignExampleData();

private:
    void firstPhaseStart();
    void secondPhaseEnd();
    void createListForFirstPhase(TeamPtrList &teams1) const;
    void createListForSecondPhase(TeamPtrList &teams2a, TeamPtrList &teams2b) const;

public:
    /// GETTERS
    QString getName() const;
    QString getFirstPhaseDate() const;
    QString getSecondPhaseDate() const;
    QString getCompetitionOrganizer() const;
    QString getFirstPhasePlace() const;
    QString getSecondPhasePlace() const;
    QString getUnionDelegate() const;
    QStringList getJudges() const;

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
    void setName(QString name);
    void setFirstPhaseDate(QString firstPhaseDate);
    void setSecondPhaseDate(QString secondPhaseDate);
    void setCompetitionOrganizer(QString competitionOrganizer);
    void setFirstPhasePlace(QString firstPhasePlace);
    void setSecondPhasePlace(QString secondPhasePlace);
    void setUnionDelegate(QString unionDelegate);
    void setJudges(QStringList judges);

    /// MODIFIERS
    Q_INVOKABLE void addJudge();
    Q_INVOKABLE void deleteJudge(int index);
    Q_INVOKABLE void setJudge(int index, QString judge);
    
signals:
    /// VARIABLE SIGNALS
    void nameChanged();
    void firstPhaseDateChanged();
    void secondPhaseDateChanged();
    void competitionOrganizerChanged();
    void firstPhasePlaceChanged();
    void secondPhasePlaceChanged();
    void unionDelegateChanged();
    void judgesChanged();

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
    QString m_firstPhaseDate;
    QString m_secondPhaseDate;
    QString m_competitionOrganizer;
    QString m_firstPhasePlace;
    QString m_secondPhasePlace;
    QString m_unionDelegate;
    QStringList m_judges;

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
