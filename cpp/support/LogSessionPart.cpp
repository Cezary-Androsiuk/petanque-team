#include "LogSessionPart.h"

LogSessionPart::LogSessionPart(
    Log::Type logType,
    const QString &function,
    const QString &message,
    QObject *parent)

    : QObject{parent}
    , m_logType{logType}
    , m_function{function}
    , m_message{message}
{ }

Log::Type LogSessionPart::getLogType() const
{
    return m_logType;
}

const QString &LogSessionPart::getFunction() const
{
    return m_function;
}

const QString &LogSessionPart::getMessage() const
{
    return m_message;
}
