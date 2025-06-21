#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

class NetworkManager : public QObject
{
    Q_OBJECT

    enum class Action{
        None,
        Authentication,
        SendingData
    };

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

public slots:
    void authenticateCredentials(QString login, QString passwordHash);
    void sendData(QString login, QString passwordHash, QString data);

private slots:
    void handleResponse();

private:
    void deleteReply();
    void handleAuthenticationResponse();
    void handleSendingDataResponse();

signals:
    void credentialsCorrect();
    void credentialsInvalid();
    void credentialsVerificationFailed(QString details);

private:
    Action m_action;

    QNetworkAccessManager * const m_networkManager;
    QNetworkReply *m_reply;

    struct{
        int statusCode;
        QJsonObject jsonData;
    } m_lastResponse;
};

#endif // NETWORKMANAGER_H
