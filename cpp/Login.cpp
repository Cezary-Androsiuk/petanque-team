#include "Login.h"

#include "support/Log.h"

Login::Login(QObject *parent)
    : QObject{parent}
{}

QString Login::computePasswordHash(QString password)
{
    QByteArray passwordBytes = password.toUtf8();

    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha3_512);
    hash.addData(passwordBytes);
    return QString(hash.result().toHex());
}

void Login::authenticate(QString login, QString password)
{
    D("login: " + login);
    D("password: " + password);

    if(login.isEmpty())
    {
        I("Login is empty!");
        emit this->authenticationFailed(tr("Login cannot be empty!"));
        return;
    }

    if(password.isEmpty())
    {
        I("Password is empty!");
        emit this->authenticationFailed(tr("Password field cannot be empty!"));
        return;
    }

    m_login = login;
    m_passwordHash = Login::computePasswordHash(password);

    // D("m_login: " + m_login)
    // D("m_passwordHash: " + m_passwordHash)

    D("");
    emit this->needCredentialsCheck(m_login, m_passwordHash);
}

void Login::onCredentialsCorrect()
{
    D("onCredentialsCorrect");
    emit this->authenticated();
}

void Login::onCredentialsInvalid()
{
    D("onCredentialsInvalid");
    emit this->authenticationFailed(tr("Invalid credentials!"));
}

void Login::onAuthenticationFailed()
{
    D("onAuthenticationFailed");
    emit this->authenticationFailed(tr("Server connection failed!"));
}
