#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_eventPtr(QSharedPointer<Event>::create(nullptr))
{}

QSharedPointer<Event> Backend::getEventPtr()
{
    return m_eventPtr;
}
