#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QSharedPointer>

class Serializable
{
public:
    virtual ~Serializable();

    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& data) = 0;
};

typedef QSharedPointer<Serializable> SerializablePtr;

#endif // SERIALIZABLE_H
