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

    this->sendRequest();

    this->waitForResponse();
}

void Login::sendRequest()
{
    D("sending request to server...");

    /// send request to server

}

void Login::waitForResponse()
{
    D("waiting for response...");

    /// temp
    bool credentialsCorrected = true;

    if(credentialsCorrected)
    {
        emit this->authenticated();
    }
    else
    {
        emit this->authenticationFailed(tr("Invalid credentials!"));
    }
}
