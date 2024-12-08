#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_eventPtr(new Event(this))
{}

Event *Backend::getEventPtr()
{
    return m_eventPtr.data();
}
