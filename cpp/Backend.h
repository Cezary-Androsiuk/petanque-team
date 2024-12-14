#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/Event.h"
#include "cpp/storages/Memory.h"

#define DEBUG_MODE true

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Memory *memory READ getMemoryPtrQml CONSTANT FINAL)
    Q_PROPERTY(Event *event READ getEventPtrQml NOTIFY eventChanged FINAL)
    Q_PROPERTY(bool isDebugMode READ getIsDebugMode CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

public slots:
    void restartEvent();

public:
    Memory *getMemoryPtrQml() const;
    Event *getEventPtrQml() const;

    bool getIsDebugMode() const;

signals:
    void eventChanged();

    void restartedEvent();

private:
    const QSharedPointer<Memory> m_memoryPtr;
    QSharedPointer<Event> m_eventPtr;
};

#endif // BACKEND_H
