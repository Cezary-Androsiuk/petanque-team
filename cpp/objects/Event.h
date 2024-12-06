#ifndef EVENT_H
#define EVENT_H

#include <QObject>

#include "cpp/Serializable.h"

class Event : public QObject, public Serializable
{
    Q_OBJECT

public:
    explicit Event(QObject *parent = nullptr);

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

signals:
};

#endif // EVENT_H
