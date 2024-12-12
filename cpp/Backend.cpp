#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_eventPtr(QSharedPointer<Event>::create(nullptr))
{
    I(QAPF("Creating Backend: %p", this));
}

Backend::~Backend()
{
    I(QAPF("Destroying Backend: %p", this));
}

QSharedPointer<Event> Backend::getEventPtr()
{
    return m_eventPtr;
}

Event *Backend::getEventPtrQml() const
{
    return m_eventPtr.data();
}
