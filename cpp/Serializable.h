#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable
{
public:
    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& data) = 0;
    virtual ~Serializable() = default;
};

#endif // SERIALIZABLE_H
