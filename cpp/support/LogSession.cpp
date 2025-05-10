#include "LogSession.h"

LogSession::LogSession(QObject *parent)
    : QObject{parent}
{}

LogSession::~LogSession()
{
    for(int i=0; i<m_parts.size(); i++)
        delete m_parts[i];
}

void LogSession::addPart(
    Log::Type logType,
    const QString &function,
    const QString &message)
{
    m_parts.append( new LogSessionPart( logType, function, message ) );
    emit this->sessionChanged();
}

const LogSessionPartRPtrList &LogSession::getParts() const
{
    return m_parts;
}
