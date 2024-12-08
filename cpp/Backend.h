#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/Event.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const Event *event READ getEventPtrQml CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    QSharedPointer<Event> getEventPtr();
    const Event *getEventPtrQml() const;

private:
    QSharedPointer<Event> m_eventPtr;
};

#endif // BACKEND_H
