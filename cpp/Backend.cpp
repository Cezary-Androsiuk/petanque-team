#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_memoryPtr(QSharedPointer<Memory>::create(nullptr))
    , m_eventPtr(QSharedPointer<Event>::create(nullptr))
{
    DOLT(this)

    m_memoryPtr->setSerializablePtr(m_eventPtr);
}

Backend::~Backend()
{
    DOLT(this)
}

void Backend::restartEvent()
{
    m_eventPtr.clear();
    m_eventPtr = QSharedPointer<Event>::create(nullptr);
    emit this->eventChanged();

    m_memoryPtr->setSerializablePtr(m_eventPtr);
    emit this->restartedEvent();
    I("event restarted")
}

Memory *Backend::getMemoryPtrQml() const
{
    return m_memoryPtr.data();
}

Event *Backend::getEventPtrQml() const
{
    return m_eventPtr.data();
}

bool Backend::getIsDebugMode() const
{
    return DEBUG_MODE;
}
