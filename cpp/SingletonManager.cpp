#include "SingletonManager.h"

#include "DoubleStartProtection.h"
#include "storages/Personalization.h"
#include "support/Log.h"

SingletonManager::SingletonManager()
{
    Log::instance = new Log();
    TRM; DOLT; /// after log creation

    DoubleStartProtection::instance = new DoubleStartProtection();

    Personalization::instance = new Personalization();
}

SingletonManager::~SingletonManager()
{TRM; DOLT;

    if(Personalization::instance)
        delete Personalization::instance;
    Personalization::instance = nullptr;

    if(DoubleStartProtection::instance)
        delete DoubleStartProtection::instance;
    DoubleStartProtection::instance = nullptr;

    if(Log::instance)
        delete Log::instance;
    Log::instance = nullptr;
}
