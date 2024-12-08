#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QObject>
#include <QJsonObject>

class Serializable: virtual public QObject
{
    Q_OBJECT
public:
    explicit Serializable(QObject *parent = nullptr);
    virtual ~Serializable();

    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& data) = 0;
};

#endif // SERIALIZABLE_H
