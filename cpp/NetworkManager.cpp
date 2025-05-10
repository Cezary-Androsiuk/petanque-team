#include "NetworkManager.h"

#include "support/Log.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
    , m_action{Action::None}
{}

void NetworkManager::authenticateCredentials(QString login, QString passwordHash)
{
    D("");
    m_action = Action::Authentication;

    // QObject::connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleResponse);
    handleResponse(); // temporary;
}

void NetworkManager::sendData(QString login, QString passwordHash, QString data)
{
    D("");
    m_action = Action::SendingData;

    // QObject::connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleResponse);
    handleResponse(); // temporary;
}

void NetworkManager::handleResponse()
{
    D("");
    switch (m_action) {
    case Action::None:
        W("No action was selected but go response");
        break;
    case Action::Authentication:
        this->handleAuthenticationResponse();
        break;
    case Action::SendingData:
        this->handleSendingDataResponse();
        break;
    default:
        W("Unknown action");
        break;
    }

    m_action = Action::None;
}

void NetworkManager::handleAuthenticationResponse()
{
    D("");
    emit this->credentialsCorrect();
    // emit this->credentialsInvalid();
}

void NetworkManager::handleSendingDataResponse()
{
    D("");

}
