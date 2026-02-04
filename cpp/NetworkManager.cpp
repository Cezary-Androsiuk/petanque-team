#include "NetworkManager.h"

#include "support/Log.h"
#include "storages/Personalization.h"

#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrl>
#include <QUrlQuery>

#include "storages/Personalization.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
    , m_action{Action::None}
    , m_reply{nullptr}
    , m_networkManager{new QNetworkAccessManager(this)}
    , m_lastResponse{-1, QJsonObject()}
{TRM; DOLTV(SAPF("%p", parent));

}

NetworkManager::~NetworkManager()
{TRM; DOLT;

}

void NetworkManager::authenticateCredentials(QString login, QString passwordHash)
{TRM;
    if(!Personalization::getInstance()->getUseExternalServer())
    {
        emit this->credentialsCorrect();
        return;
    }

    if(m_reply)
    {
        D("still waiting for the reply, can't start the new one");
        return;
    }

    m_action = Action::Authentication;

    QUrl url(Personalization::getInstance()->getServerAddress());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::UserAgentHeader, "PetanqueTeam/1.0");

    QJsonObject jsonObject;
    jsonObject["action"] = "auth";
    jsonObject["login"] = login;
    jsonObject["password_hash"] = passwordHash;

    QByteArray requestData;
    QJsonDocument jsonDoc(jsonObject);
    requestData = jsonDoc.toJson(QJsonDocument::JsonFormat::Compact);

    m_reply = m_networkManager->post(request, requestData);
    QObject::connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleResponse);
}

void NetworkManager::sendData(QString login, QString passwordHash, QString data)
{TRM;

    if(!Personalization::getInstance()->getUseExternalServer())
    {
        return;
    }

    m_action = Action::SendingData;

    // QObject::connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleResponse);
    handleResponse(); // temporary;
}

void NetworkManager::handleResponse()
{TRM;

    m_lastResponse.jsonData = QJsonObject();
    m_lastResponse.statusCode = -1;

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
    this->deleteReply();
}

void NetworkManager::deleteReply()
{TRM;

    if(!m_reply)
    {
        W("reply was already deleted");
        return;
    }

    bool disconnectStatus =
        QObject::disconnect(
            m_reply, &QNetworkReply::finished,
            this, &NetworkManager::handleResponse);
    D("reply disconnect status: %s", disconnectStatus ? "correctly broken" : "failed");
    delete m_reply;
    m_reply = nullptr;
}

void NetworkManager::handleAuthenticationResponse()
{TRM;

    if(!m_reply)
    {
        D("reply not exist");
        emit this->credentialsVerificationFailed("Nie otrzymano odpowiedzi!");
        return;
    }

    m_lastResponse.statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responseData = m_reply->readAll();

    /// check for communication error
    // if(m_reply->error() != QNetworkReply::NoError)
    if(m_lastResponse.statusCode != 200) /// if input data are correct, this is only code that could be sended
    {
        D("status code: %d", m_lastResponse.statusCode);
        D("reply error: " + m_reply->errorString());
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        if(!jsonDocument.isNull())
        {
            /// can add some stuff to display more info in popup
            D("response data:");
            R(QString(jsonDocument.toJson()));
        }

        emit this->credentialsVerificationFailed("Błąd: " + m_reply->errorString());
        return;
    }

    /// at this point no error from server - all fine

    QJsonDocument responseJson = QJsonDocument::fromJson(responseData);
    if(responseJson.isNull())
    {
        /// can't read non JSON response
        D("Can't read JSON from response");
        emit this->credentialsVerificationFailed("Nie można odczytać odpowiedzi");
        return;
    }

    DA(Log::Action::Save, "response json is OK");

    QJsonObject rootJsonObject = responseJson.object();

    QString status = rootJsonObject["status"].toString();
    if(status.isNull())
    {
        D("Can't read status from JSON");
        emit this->credentialsVerificationFailed("Nie można odczytać statusu z odpowiedzi");
        return;
    }

    if(status == "success")
    {
        emit this->credentialsCorrect();
    }
    else if(status == "failed")
    {
        emit this->credentialsInvalid();
    }
    else
    {
        D("Unknown status: " + status);
        emit this->credentialsVerificationFailed("Nieobsługiwany status: " + status);
        return;
    }
}

void NetworkManager::handleSendingDataResponse()
{TRM;


}
