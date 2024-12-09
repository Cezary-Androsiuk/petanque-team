#ifndef SUBPHASE_H
#define SUBPHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class SubPhase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit SubPhase(QObject *parent = nullptr);
    ~SubPhase();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

    void clear();

signals:

private:
};

typedef QSharedPointer<SubPhase> SubPhasePtr;
typedef QVector<SubPhasePtr> SubPhasePtrVector;
typedef QVector<const SubPhase *> QmlSubPhasePtrVector;

#endif // SUBPHASE_H
