#include "DoubleStartProtection.h"

#include "support/Log.h"

DoubleStartProtection::DoubleStartProtection(QObject *parent)
    : QObject{parent}
{}

DoubleStartProtection * const DoubleStartProtection::getInstance() noexcept
{
    static DoubleStartProtection i;
    return &i;
}

void DoubleStartProtection::verify() noexcept
{
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
{
    D("testing IfApplicationAlreadyRunning");
    static QSharedMemory sharedMemory;
    sharedMemory.setKey(UNIQUE_KEY_PREVENT_DOUBLE_RUN);

    return sharedMemory.create(1);
}
