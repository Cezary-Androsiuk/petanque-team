#include "Login.h"

#include "support/Log.h"

Login::Login(QObject *parent)
    : QObject{parent}
{TR;
}

QString Login::computePasswordHash(QString password)
{TR;
    QByteArray passwordBytes = password.toUtf8();

    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha3_512);
    hash.addData(passwordBytes);
    return QString(hash.result().toHex());
}

void Login::authenticate(QString login, QString password)
{TR;
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

    emit this->needCredentialsCheck(m_login, m_passwordHash);
}

void Login::onCredentialsCorrect()
{TR;
    emit this->authenticated();
}

void Login::onCredentialsInvalid()
{TR;
    emit this->authenticationFailed(tr("Invalid credentials!"));
}

void Login::onAuthenticationFailed(QString details)
{TR;
    emit this->authenticationFailed(tr("Server connection failed!")/* + " " + details*/);
}
