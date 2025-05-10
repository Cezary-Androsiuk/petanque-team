#include "SingletonManager.h"

#include "support/Log.h"
#include "storages/Personalization.h"

SingletonManager::SingletonManager()
{
    Log::instance = new Log();

    Personalization::instance = new Personalization();
}

SingletonManager::~SingletonManager()
{

    if(Personalization::instance)
        delete Personalization::instance;
    Personalization::instance = nullptr;

    if(Log::instance)
        delete Log::instance;
    Log::instance = nullptr;
}
