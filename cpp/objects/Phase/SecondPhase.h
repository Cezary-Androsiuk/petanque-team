#ifndef SECONDPHASE_H
#define SECONDPHASE_H

#include <QObject>

#include "Phase.h"

class SecondPhase : public Phase
{
    Q_OBJECT
public:
    explicit SecondPhase(QObject *parent = nullptr);

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

    void clear() override;

signals:
};

typedef QSharedPointer<SecondPhase> SecondPhasePtr;

#endif // SECONDPHASE_H
