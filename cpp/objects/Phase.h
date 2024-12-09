#ifndef PHASE_H
#define PHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/SubPhase.h"

class Phase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Phase(int subPhasesCount, QObject *parent = nullptr);
    ~Phase();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &phaseJson) override;

    void clear();

private:
    SubPhasePtrVector m_subPhases;
};

typedef QSharedPointer<Phase> PhasePtr;
typedef QVector<PhasePtr> PhasePtrVector;
typedef QVector<const Phase *> QmlPhasePtrVector;

#endif // PHASE_H
