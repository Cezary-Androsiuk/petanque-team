#include "DoubleStartProtection.h"

#include "support/Log.h"

DoubleStartProtection *DoubleStartProtection::instance = nullptr;

DoubleStartProtection::DoubleStartProtection(QObject *parent)
    : QObject{parent}
{TRM; DOLTV(SAPF("%p", parent));

}

DoubleStartProtection::~DoubleStartProtection()
{TRM; DOLT;

}

DoubleStartProtection * const DoubleStartProtection::getInstance() noexcept
{TRF;
    // static DoubleStartProtection i;
    return instance;
}

void DoubleStartProtection::verify() noexcept
{TRM;
    /// test shared memory
    if(!DoubleStartProtection::testIfApplicationAlreadyRunning())
    {
        /// application won't continue if so, just inform user about it
        W("Application is already running");
        emit this->applicationIsAlreadyRunning();
        return;
    }

    emit this->verified();
}

bool DoubleStartProtection::testIfApplicationAlreadyRunning() noexcept
{TRF;
    D("testing IfApplicationAlreadyRunning");
    static QSharedMemory sharedMemory;
    sharedMemory.setKey(UNIQUE_KEY_PREVENT_DOUBLE_RUN);

    return sharedMemory.create(1);
}
