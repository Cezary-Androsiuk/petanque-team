#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QCryptographicHash>
#include <QByteArray>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);

private:
    static QString computePasswordHash(QString password);

public slots:
    void authenticate(QString login, QString password);

    void onCredentialsCorrect();
    void onCredentialsInvalid();

signals:
    void needCredentialsCheck(QString login, QString passwordHash);

    void authenticated();
    void authenticationFailed(QString message);

private:
    QString m_login;
    QString m_passwordHash;
};

#endif // LOGIN_H
