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
    ~Login();

private:
    static QString computePasswordHash(QString password);

public slots:
    void authenticate(QString login, QString password);

    /// called by signals emited by NetworkManager (connected in Backend)
    void onCredentialsCorrect();
    void onCredentialsInvalid();
    void onAuthenticationFailed(QString details);

signals:
    void needCredentialsCheck(QString login, QString passwordHash);

    /// signals for QML
    void authenticated();
    void authenticationFailed(QString message);

private:
    QString m_login;
    QString m_passwordHash;
};

#endif // LOGIN_H
