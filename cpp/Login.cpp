#include "Login.h"

#include "support/Log.h"

Login::Login(QObject *parent)
    : QObject{parent}
{TRM; DOLTV(SAPF("%p", parent));
}

Login::~Login()
{TRM; DOLT;

}

QString Login::computePasswordHash(QString password)
{TRF;
    QByteArray passwordBytes = password.toUtf8();

    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha3_512);
    hash.addData(passwordBytes);
    return QString(hash.result().toHex());
}

void Login::authenticate(QString login, QString password)
{TRM;
    D("login: " + login);
    D("password: " + password);

    if(login.isEmpty())
    {
        I("Login is empty!");
        emit this->authenticationFailed(tr("Login jest wymagany!"));
        return;
    }

    if(password.isEmpty())
    {
        I("Password is empty!");
        emit this->authenticationFailed(tr("Hasło jest wymagane!"));
        return;
    }

    m_login = login;
    m_passwordHash = Login::computePasswordHash(password);

    // D("m_login: " + m_login)
    // D("m_passwordHash: " + m_passwordHash)

    emit this->needCredentialsCheck(m_login, m_passwordHash);
}

void Login::onCredentialsCorrect()
{TRM;
    emit this->authenticated();
}

void Login::onCredentialsInvalid()
{TRM;
    emit this->authenticationFailed(tr("Niepoprawne dane!"));
}

void Login::onAuthenticationFailed(QString details)
{TRM;
    emit this->authenticationFailed(tr("Nie można połączyć się z serwerem!")/* + " " + details*/);
}
