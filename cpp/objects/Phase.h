#ifndef PHASE_H
#define PHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "Serializable.h"
#include "objects/SubPhase.h"
#include "enums/PhaseEnum.h"

#define SERL_SUB_PHASES_KEY "sub phases"

typedef QList<TeamPtrList> TeamPtrLists;

class Phase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int subPhasesCount READ getSubPhasesCount CONSTANT FINAL)
    Q_PROPERTY(QmlSubPhasePtrVector subPhases READ getSubPhasesQml CONSTANT FINAL)

public:
    explicit Phase(PhaseEnum phase, QObject *parent = nullptr);
    ~Phase();

    void onStart();
    void onEnd();

    void initSubPhases(const TeamPtrLists &listsOfTeams);

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jPhase) override;
    void deserializeSubPhases(const QJsonObject &jPhase);

    void clear(bool emitting = true);

public slots:
    void verify();
    bool hasNext();
    void goToNext();

    void assignExampleData();

private:
    void subPhaseStart();
    void subPhaseEnd();

public:
    /// GETTERS
    int getSubPhasesCount() const;
    const SubPhasePtrVector &getSubPhases() const;

    QString getCurrentName() const;
    QString getNextName() const;

    /// QML GETTERS
    QmlSubPhasePtrVector getSubPhasesQml() const;

signals:
    void verified();
    void verificationFailed(QString message);

private:
    /// This object phase - First or Second - is set while creation in Event class
    const PhaseEnum m_phase;

    /// if Phase is First then subphases vector contains one subphase
    /// if Phase is Second then subphases vector contains two subphases
    SubPhasePtrVector m_subPhases; /// const, but cant be marked as const :/ due to way this is initialized and serialization
};

typedef QSharedPointer<Phase> PhasePtr;
typedef QVector<PhasePtr> PhasePtrVector;
typedef QVector<Phase *> QmlPhasePtrVector;

#endif // PHASE_H
