#include "LogQML.h"

LogQML::LogQML(QObject *parent)
    : QObject{parent}
{}

void LogQML::i(cQS log, QString func)
{
    Log::info( QML_LOG_PREFIX(func), log );
}

void LogQML::w(cQS log, QString func)
{
    Log::warning( QML_LOG_PREFIX(func), log );
}

void LogQML::e(cQS log, QString func)
{
    Log::error( QML_LOG_PREFIX(func), log );
}

void LogQML::d(cQS log, QString func)
{
    Log::debug( QML_LOG_PREFIX(func), log );
}
