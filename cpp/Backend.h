#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/Event.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Event *event READ getEventPtr CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);

    Event *getEventPtr();

private:
    QPointer<QObject> m_eventPtr;
};

#endif // BACKEND_H
