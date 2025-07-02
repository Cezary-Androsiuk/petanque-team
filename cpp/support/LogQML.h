#ifndef LOGQML_H
#define LOGQML_H

#include <QObject>

#include "support/Log.h"

#define QML_LOG_PREFIX(funcName) (funcName.isEmpty() ? QString("QML(...)") : ("QML(" + funcName + ")")).toStdString()

class LogQML : public QObject
{
    Q_OBJECT
public:
    explicit LogQML(QObject *parent = nullptr);

    typedef const QString &cQS;

public slots:
    Log::Action toAction(const QString &action);
    Log::Action toAction(int action);

public slots:
    void i(cQS log, QString func = "", Log::Action action = Log::Action::All);
    void w(cQS log, QString func = "", Log::Action action = Log::Action::All);
    void e(cQS log, QString func = "", Log::Action action = Log::Action::All);
    void d(cQS log, QString func = "", Log::Action action = Log::Action::All);
    void t(cQS file, cQS func, int line = 0, cQS funcArgs = "");

    QString getCurrentSession();

signals:
};

#endif // LOGQML_H
