#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>

#include <QPointer>
#include <QFile>
#include <QFileInfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"


#define MEMORY_FILE "petanque_team_memory.json"
#define DELETE_MEMORY_AT_START false
#define PRINT_VALUES false // if true, prints values after loadPersonalization and before savePersonalization

class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = nullptr);

    void setSerializablePtr(const QPointer<Serializable> &serializablePtr);

public slots:
    void load();
    void save();

    bool debugMemoryFileExist();
    void debugDeleteMemory();

signals:
    void memoryFileNotExist();

    void memorySaved();
    void memoryLoaded();

    void memorySaveError(const QString &message);
    void memoryLoadError(const QString &message);

private:
    QPointer<QObject> m_serializablePtr;
};

#endif // MEMORY_H
