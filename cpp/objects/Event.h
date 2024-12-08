#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"
#include "cpp/objects/Phase.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_EVENT_NAME_KEY     "name"
#define SERL_CURRENT_PHASE_KEY  "current phase"
#define SERL_PHASES_KEY         "phases"

class Event : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(PhasePtr currentPhase READ getCurrentPhasePtr NOTIFY phasesChanged FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &eventJson) override;

    void clear(bool emitting = true);

private:
    void initialize();
    void createPhases();

public:
    QString getName() const;
    PhasePtr getCurrentPhasePtr() const;
    // PhasePtrVector getPhases() const;

    void setName(const QString &name);
    
signals:
    void nameChanged();
    void currentPhaseChanged();
    void phasesChanged();

private:
    QString m_name;
    int m_currentPhase;
    PhasePtrVector m_phases;
};

#endif // EVENT_H
