#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/Event.h"

#define DEBUG_MODE true

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Event *event READ getEventPtrQml CONSTANT FINAL)
    Q_PROPERTY(bool isDebugMode READ getIsDebugMode CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    QSharedPointer<Event> getEventPtr();
    Event *getEventPtrQml() const;

    bool getIsDebugMode() const;

private:
    QSharedPointer<Event> m_eventPtr;
};

#endif // BACKEND_H
