#ifndef PHASE_H
#define PHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/SubPhase.h"
#include "cpp/enums/PhaseEnum.h"

class Phase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int subPhasesCount READ getSubPhasesCount CONSTANT FINAL)
    Q_PROPERTY(QmlSubPhasePtrVector subPhases READ getSubPhasesQml CONSTANT FINAL)

public:
    explicit Phase(PhaseEnum phase, int subPhasesCount, QObject *parent = nullptr);
    ~Phase();

private:
    void initSubPhases();

public:

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &phaseJson) override;

    void clear();

public:
    int getSubPhasesCount() const;
    const SubPhasePtrVector &getSubPhases() const;

    /// QML LIST GETTERS
    QmlSubPhasePtrVector getSubPhasesQml() const;

private:
    const PhaseEnum m_phase;
    const int m_subPhasesCount;
    const SubPhasePtrVector m_subPhases;
};

typedef QSharedPointer<Phase> PhasePtr;
typedef QVector<PhasePtr> PhasePtrVector;
typedef QVector<Phase *> QmlPhasePtrVector;

#endif // PHASE_H
