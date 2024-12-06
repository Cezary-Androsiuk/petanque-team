#ifndef LOGQML_H
#define LOGQML_H

#include <QObject>

#include "cpp/support/Log.h"

#define QML_LOG_PREFIX(funcName) (funcName.isEmpty() ? QString("QML(...)") : ("QML(" + funcName + ")"))

class LogQML : public QObject
{
    Q_OBJECT
public:
    explicit LogQML(QObject *parent = nullptr);

    typedef const QString &cQS;

public slots:
    void i(cQS log, QString func = "");
    void w(cQS log, QString func = "");
    void e(cQS log, QString func = "");
    void d(cQS log, QString func = "");

signals:
};

#endif // LOGQML_H
