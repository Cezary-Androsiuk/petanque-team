#ifndef FIRSTPHASE_H
#define FIRSTPHASE_H

#include <QObject>

#include "Phase.h"

class FirstPhase : public Phase
{
    Q_OBJECT
public:
    explicit FirstPhase(QObject *parent = nullptr);

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

    void clear() override;

signals:
};

typedef QSharedPointer<FirstPhase> FirstPhasePtr;

#endif // FIRSTPHASE_H
