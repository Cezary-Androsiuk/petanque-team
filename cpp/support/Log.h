#ifndef LOG_H
#define LOG_H

#include <cstdio>

#include <QString>
#include <QList>
#include <QUrl>

#include <fstream>
#include <cstdarg> // va_list

// #include "LogSession.h"

#define SAPF(...) Log::asprintf(__VA_ARGS__) /* string as printf */

#define DISPLAY_OBJECT_LIFE_TIME true

/// Display Object Life Time Variable - Force
#define DOLTV_F(ptr, argsStr) {                                             \
    QString f_name(__FUNCTION__);                                           \
    if(f_name.isEmpty())      f_name = "unknown action";                    \
    if(f_name[0] == '~')    f_name = "Destroying " + f_name;                \
    else                    f_name = "Creating " + f_name;                  \
    QString qargsStr(argsStr);                                              \
    if(!qargsStr.isEmpty()) qargsStr = "(" + qargsStr + ")";                \
    DA(Log::Action::SaveSession, f_name + qargsStr + SAPF(": %p", ptr));    \
}

/// Display Object Life Time - Force
#define DOLT_F(ptr) DOLTV_F(ptr, "")

/// Display Object Life Time Variable
#define DOLTV(ptr, argsStr) if(DISPLAY_OBJECT_LIFE_TIME) { DOLTV_F(ptr, argsStr) }

/// Display Object Life Time
#define DOLT(ptr) DOLTV(ptr, "")




#define I(...) Log::getInstance()->info    (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__)) // info
#define W(...) Log::getInstance()->warning (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__)) // warning
#define E(...) Log::getInstance()->error   (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__)) // error
#define D(...) Log::getInstance()->debug   (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__)) // debug
#define R(...) Log::getInstance()->raw     (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__)) // raw

#define IA(a, ...) Log::getInstance()->info    (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__), Log::Action(a)); // info
#define WA(a, ...) Log::getInstance()->warning (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__), Log::Action(a)); // warning
#define EA(a, ...) Log::getInstance()->error   (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__), Log::Action(a)); // error
#define DA(a, ...) Log::getInstance()->debug   (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__), Log::Action(a)); // debug
#define RA(a, ...) Log::getInstance()->raw     (__PRETTY_FUNCTION__, SAPF(__VA_ARGS__), Log::Action(a)); // raw



extern const char *outputDirectory;

#define EST_FUNCTION_LENGTH 70 // estimated function name length what will be reserved while creating log
#define SHORTER_FUNCTION_FILL_CHARACTER ' ' // characters that fills area before function name to fit estimated function name length
#define CONTENT_SPACE 10 // space between function name and content
#define CONTENT_SPACE_CHARACTER ' ' // characters that fills space between function name and content
#define SPACE_BETWEEN_CONTENT_SPACE_AND_CONTENT true // creates spaces between space: "x ........ y" instead of "x........y"

class Log
{
public:
    enum class Type{
        Info,
        Warning,
        Error,
        Debug,
        Raw,
    };
    static const char *logTypeToStr(Type type);

    enum Action{
        None = 0,
        Save = 1 << 0,
        Print = 1 << 1,
        Session = 1 << 2,
        SavePrint = Save | Print,
        SaveSession = Save | Session,
        PrintSession = Print | Session,
        All = Save | Print | Session,
    };
    static const char *logActionToStr(Action action);

    typedef const std::string &cstr;
    typedef const QString &cQS;

    static constexpr Action actionForceHighest = Action::All; // set highest ( will be compared with & sign )
    static constexpr Action actionForceLowest = Action::None;  // set lowest ( will be compared with | sign )

    static Log *getInstance();

    void info(cQS func, cQS log, Action action = Action(Action::All));
    void warning(cQS func, cQS log, Action action = Action(Action::All));
    void error(cQS func, cQS log, Action action = Action(Action::All));
    void debug(cQS func, cQS log, Action action = Action(Action::All));
    void raw(cQS func, cQS log, Action action = Action(Action::All));

    static QString asprintf(const char *text, ...);
    static QString asprintf(cQS text, ...);
    static QString asprintf(int);

private:
    std::string time(bool simpleSeparators = false);
    std::string buildPrefix(Type logType, cstr funName);
    std::string buildStartPrefix();

    void log(Type logType, cstr funName, cstr log, Action action = Action::All);
    void safeLog(Type logType, cstr funName, cstr log, Action action = Action::All);
    void print(cstr content, bool newLine = true);
    void openFile();
    void saveFile(cstr content);
    void addSession(cstr content, bool newLine = true);
    // void addSession(Type logType, cstr funName, cstr message);

public:
    class Convert{
    public:
        static QString listUrlToString(QList<QUrl> list);
        static QString listStrToString(QList<QString> list);
    };

private:
    // static LogSession currentSession;
    std::string currentSession;

    std::string m_fileName;
    std::ofstream m_outFile;

    static Log* instance;
    friend class LogQML;
    friend class SingletonManager;
};

#endif // LOG_H
