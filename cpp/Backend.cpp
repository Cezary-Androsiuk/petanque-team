#include "Backend.h"

#include "support/Log.h"
#include "DebugConstraints.h"

const char *version = "v0.4.2";

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_loginPtr(QSharedPointer<Login>::create(nullptr))
    , m_networkManager(QSharedPointer<NetworkManager>::create(nullptr))
    , m_memoryPtr(QSharedPointer<Memory>::create(nullptr))
    , m_eventPtr(QSharedPointer<Event>::create(nullptr))
{TRM; DOLTV(SAPF("%p", parent));

    QObject::connect(m_loginPtr.data(), &Login::needCredentialsCheck, m_networkManager.data(), &NetworkManager::authenticateCredentials);
    QObject::connect(m_networkManager.data(), &NetworkManager::credentialsCorrect, m_loginPtr.data(), &Login::onCredentialsCorrect);
    QObject::connect(m_networkManager.data(), &NetworkManager::credentialsInvalid, m_loginPtr.data(), &Login::onCredentialsInvalid);
    QObject::connect(m_networkManager.data(), &NetworkManager::credentialsVerificationFailed, m_loginPtr.data(), &Login::onAuthenticationFailed);

    m_memoryPtr->setSerializablePtr(m_eventPtr);
}

Backend::~Backend()
{TRM; DOLT;

}

void Backend::restartEvent()
{TRM;
    m_eventPtr.clear();
    m_eventPtr = QSharedPointer<Event>::create(nullptr);
    emit this->eventChanged();

    m_memoryPtr->setSerializablePtr(m_eventPtr);
    emit this->restartedEvent();
    I("event restarted");
}

Login *Backend::getLoginPtrQml() const
{TRM;
    return m_loginPtr.data();
}

Memory *Backend::getMemoryPtrQml() const
{TRM;
    return m_memoryPtr.data();
}

Event *Backend::getEventPtrQml() const
{TRM;
    return m_eventPtr.data();
}

bool Backend::getIsDebugMode() const
{TRF;
    return DEBUG_MODE;
}

bool Backend::getEnabledPopups() const
{TRF;
    return ENABLE_POPUPS;
}
