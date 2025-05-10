#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSharedPointer>

#include "Login.h"
#include "NetworkManager.h"
#include "objects/Event.h"
#include "storages/Memory.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Login *login READ getLoginPtrQml CONSTANT FINAL)
    Q_PROPERTY(Memory *memory READ getMemoryPtrQml CONSTANT FINAL)
    Q_PROPERTY(Event *event READ getEventPtrQml NOTIFY eventChanged FINAL)
    Q_PROPERTY(bool isDebugMode READ getIsDebugMode CONSTANT FINAL)
    Q_PROPERTY(bool enabledPopups READ getEnabledPopups CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

public slots:
    void restartEvent();

public:
    Login *getLoginPtrQml() const;
    Memory *getMemoryPtrQml() const;
    Event *getEventPtrQml() const;

    bool getIsDebugMode() const;
    bool getEnabledPopups() const;

signals:
    void eventChanged();

    void restartedEvent();

private:
    const QSharedPointer<Login> m_loginPtr;
    const QSharedPointer<NetworkManager> m_networkManager;
    const QSharedPointer<Memory> m_memoryPtr;
    QSharedPointer<Event> m_eventPtr;
};

#endif // BACKEND_H
