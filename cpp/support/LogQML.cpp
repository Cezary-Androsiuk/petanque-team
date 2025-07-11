#include "LogQML.h"

LogQML::LogQML(QObject *parent)
    : QObject{parent}
{}

Log::Action LogQML::toAction(const QString &action)
{
    QString _action = action.toLower();
    if(_action == "none")           return Log::Action::None;           else
    if(_action == "save")           return Log::Action::Save;           else
    if(_action == "print")          return Log::Action::Print;          else
    if(_action == "session")        return Log::Action::Session;        else

    if(_action == "saveprint")      return Log::Action::SavePrint;      else
    if(_action == "save print")     return Log::Action::SavePrint;      else
    if(_action == "save_print")     return Log::Action::SavePrint;      else
    if(_action == "save-print")     return Log::Action::SavePrint;      else
    if(_action == "save/print")     return Log::Action::SavePrint;      else

    if(_action == "savesession")    return Log::Action::SaveSession;    else
    if(_action == "save session")   return Log::Action::SaveSession;    else
    if(_action == "save_session")   return Log::Action::SaveSession;    else
    if(_action == "save-session")   return Log::Action::SaveSession;    else
    if(_action == "save/session")   return Log::Action::SaveSession;    else

    if(_action == "printsession")   return Log::Action::PrintSession;   else
    if(_action == "print session")  return Log::Action::PrintSession;   else
    if(_action == "print_session")  return Log::Action::PrintSession;   else
    if(_action == "print-session")  return Log::Action::PrintSession;   else
    if(_action == "print/session")  return Log::Action::PrintSession;   else

    if(_action == "all")            return Log::Action::All;            else
    {
        W(SAPF("unknown QString action: %s", action.toStdString().c_str()));
        I("returning Log::Action::All");
        return Log::Action::All;
    }
}

Log::Action LogQML::toAction(int action)
{
    int bottom = static_cast<int>(Log::Action::None);
    int top = static_cast<int>(Log::Action::All);

    if(bottom <= action && action <= top)
    {
        return static_cast<Log::Action>(action);
    }

    W(SAPF("unknown int action: %d, range is: [%d, %d]", action, bottom, top));
    I("returning Log::Action::All");
    return Log::Action::All;
}

void LogQML::i(cQS log, QString func, Log::Action action)
{
    Log::getInstance()->info( QML_LOG_PREFIX(func), log, action );
}

void LogQML::w(cQS log, QString func, Log::Action action)
{
    Log::getInstance()->warning( QML_LOG_PREFIX(func), log, action );
}

void LogQML::e(cQS log, QString func, Log::Action action)
{
    Log::getInstance()->error( QML_LOG_PREFIX(func), log, action );
}

void LogQML::d(cQS log, QString func, Log::Action action)
{
    Log::getInstance()->debug( QML_LOG_PREFIX(func), log, action );
}

void LogQML::t(cQS file, cQS func, int line, cQS funcArgs)
{
    Log::getInstance()->traceQML(file.toStdString(), func.toStdString(), line, funcArgs);
}

QString LogQML::getCurrentSession()
{
    return Log::getInstance()->getCurrentSession().c_str();
}
