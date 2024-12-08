#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>
#include <QJsonArray>

class Serializable
{
public:
    virtual ~Serializable();

    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& data) = 0;
};

#endif // SERIALIZABLE_H
