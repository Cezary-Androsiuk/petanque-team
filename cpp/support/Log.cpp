#include "cpp/support/Log.h"

bool Log::m_firstLog = true;
QString Log::m_sessionLogs = QString();

void Log::info(cQS func, cQS log, Log::Action action)
{
    Log::log("I", func, log, action);
}

void Log::warning(cQS func, cQS log, Log::Action action)
{
    Log::log("W", func, log, action);
}

void Log::error(cQS func, cQS log, Log::Action action)
{
    Log::log("E", func, log, action);
}

void Log::debug(cQS func, cQS log, Log::Action action)
{
    Log::log("D", func, log, action);
}

QString Log::time()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
}

QString Log::buildPrefix(cQS type, cQS func, bool time)
{
    QString prefix;

    // set time
    if(time)
        prefix = "[" + Log::time() +  "]" + " ";

    // set type
    prefix += type;

    prefix += " ";

    if(type == "E")
        prefix += "### ### ";
    else if(type == "W")
        prefix += "### ";

    // set function name
    if(func.length() >= EST_FUNCTION_LENGTH)
        prefix += func;
    else
    {
        size_t fill = EST_FUNCTION_LENGTH - func.length() - prefix.size();
        prefix += QString(SHORTER_FUNCTION_FILL_CHARACTER).repeated(fill);
        prefix += func;
    }

#if SPACE_BETWEEN_CONTENT_SPACE_AND_CONTENT
    prefix += " ";
#endif

    // set space between content
    prefix += QString(CONTENT_SPACE_CHARACTER).repeated(CONTENT_SPACE);

#if SPACE_BETWEEN_CONTENT_SPACE_AND_CONTENT
    prefix += " ";
#endif

    return prefix;
}

QString Log::buildStartPrefix()
{
    QString prefix;
    // set time
    prefix = "[" + Log::time() +  "]" + "   ";

    return prefix + "--- [APPLICATION STARTED] ---";
}

void Log::log(const char *type, cQS func, cQS log, Log::Action action)
{
    Action limitedAction = Action( (action | Log::actionForceLowest) & Log::actionForceHighest );

    QString logWithTime = buildPrefix(type, func, true) + log;
    QString logWithoutTime = buildPrefix(type, func, false) + log;

    if(limitedAction & Action::Print)
        Log::print(logWithoutTime);

    if(limitedAction & Action::Save)
        Log::saveFile(logWithTime);

    if(limitedAction & Action::Sesion)
        Log::addSession(logWithoutTime);
}

void Log::print(cQS content)
{
    qDebug() << content.toStdString().c_str();
}

void Log::saveFile(cQS content)
{
    QFile file(LOG_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        WR << "Error while creating info log!";
        return;
    }

    QTextStream out(&file);
    if(m_firstLog)
    {
        out << Log::buildStartPrefix() << "\n";
        m_firstLog = false;
    }
    out << content << "\n";
    file.close();
}

void Log::addSession(cQS content)
{
    Log::m_sessionLogs += content + "\n";
}

QString Log::Convert::listUrlToString(QList<QUrl> list)
{
    QString str("[");
    for(const auto &i : list)
        str += "\"" + i.toLocalFile() + "\", ";
    return str + "\b\b]";
}
