#include "Backend.h"

#include "support/Log.h"
#include "DebugConstraints.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_loginPtr(QSharedPointer<Login>::create(nullptr))
    , m_networkManager(QSharedPointer<NetworkManager>::create(nullptr))
    , m_memoryPtr(QSharedPointer<Memory>::create(nullptr))
    , m_eventPtr(QSharedPointer<Event>::create(nullptr))
{
    DOLT(this)

    QObject::connect(m_loginPtr.data(), &Login::needCredentialsCheck, m_networkManager.data(), &NetworkManager::authenticateCredentials);
    QObject::connect(m_networkManager.data(), &NetworkManager::credentialsCorrect, m_loginPtr.data(), &Login::onCredentialsCorrect);
    QObject::connect(m_networkManager.data(), &NetworkManager::credentialsInvalid, m_loginPtr.data(), &Login::onCredentialsInvalid);

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
    I("event restarted");
}

Login *Backend::getLoginPtrQml() const
{
    return m_loginPtr.data();
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

bool Backend::getEnabledPopups() const
{
    return ENABLE_POPUPS;
}
