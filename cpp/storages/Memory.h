#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = nullptr);

    void setSerializableObject

public slots:
    void load();
    void save();

signals:

private:
    Serializable *m_serializableObject;
};

#endif // MEMORY_H
