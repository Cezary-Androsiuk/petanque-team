#ifndef PHASE_H
#define PHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class Phase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Phase(QObject *parent = nullptr);
    ~Phase();

    virtual void clear() = 0;
};

typedef QSharedPointer<Phase> PhasePtr;
typedef QVector<PhasePtr> PhasePtrVector;
typedef QVector<const Phase *> QmlPhasePtrVector;

#endif // PHASE_H
