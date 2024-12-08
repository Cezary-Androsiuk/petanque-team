#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "cpp/Serializable.h"
#include "cpp/objects/Phase.h"

class Event : public QObject, public Serializable
{
    Q_OBJECT

public:
    explicit Event(QObject *parent = nullptr);

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

private:
    void initialize();
    void createPhases();

signals:

private:
    int m_currentPhase;
    QVector<QSharedPointer<Phase>> m_phases;
};

#endif // EVENT_H
