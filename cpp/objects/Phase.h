#ifndef PHASE_H
#define PHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/SubPhase.h"
#include "cpp/enums/PhaseEnum.h"
#include "cpp/storages/Personalization.h"

class Phase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int subPhasesCount READ getSubPhasesCount CONSTANT FINAL)
    Q_PROPERTY(QmlSubPhasePtrVector subPhases READ getSubPhasesQml CONSTANT FINAL)

public:
    explicit Phase(PhaseEnum phase, QObject *parent = nullptr);
    ~Phase();

    void initSubPhases();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &phaseJson) override;

    void clear();

public slots:
    void verify();
    bool hasNext();
    void goToNext();

public:
    /// GETTERS
    int getSubPhasesCount() const;
    const SubPhasePtrVector &getSubPhases() const;

    /// QML GETTERS
    QmlSubPhasePtrVector getSubPhasesQml() const;

signals:
    void verified();
    void verificationFailed(QString message);

private:
    const PhaseEnum m_phase;
    SubPhasePtrVector m_subPhases;
};

typedef QSharedPointer<Phase> PhasePtr;
typedef QVector<PhasePtr> PhasePtrVector;
typedef QVector<Phase *> QmlPhasePtrVector;

#endif // PHASE_H
