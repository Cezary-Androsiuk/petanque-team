#include "SingletonManager.h"

#include "storages/Personalization.h"
#include "support/Log.h"

SingletonManager::SingletonManager()
{
    Log::instance = new Log();
    TR; DOLT(this);

    Personalization::instance = new Personalization();
}

SingletonManager::~SingletonManager()
{TR;
    DOLT(this);

    if(Personalization::instance)
        delete Personalization::instance;
    Personalization::instance = nullptr;

    if(Log::instance)
        delete Log::instance;
    Log::instance = nullptr;
}
