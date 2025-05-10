#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

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

public slots:
    void authenticateCredentials(QString login, QString passwordHash);
    void sendData(QString login, QString passwordHash, QString data);

private slots:
    void handleResponse();

private:
    void handleAuthenticationResponse();
    void handleSendingDataResponse();

signals:
    void credentialsCorrect();
    void credentialsInvalid();

private:
    Action m_action;

};

#endif // NETWORKMANAGER_H
