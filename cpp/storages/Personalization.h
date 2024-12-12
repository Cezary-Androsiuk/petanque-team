#ifndef PERSONALIZATION_H
#define PERSONALIZATION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>

#include "cpp/support/Log.h"
#include "cpp/storages/DefaultPersonalizationData.h"

#define JSON_FILE "personalization.json"
#define PRINT_VALUES false // if true, prints values after loadPersonalization and before savePersonalization
#define KEY_NOT_FOUND_MESSAGE W(JSON_FILE " file not contains value related with key: " + key); // requires key variable
#define MARK_ERROR(x) {auto error = (x); W(error);}

#define BOOL_TO_STR(x) ( (x) ? QString("true") : QString("false") )

/// DEFAULT VALUES
#define DEFAULT_NOTE "### Any change to the contents of this file, may lead to unexpected results ###"

/// KEYS FOR VALUES
#define KEY_NOTE "!NOTE"
#define KEY_EXAMPLE_DATA "example data"
#define KEY_MINIMUM_PLAYERS_IN_TEA "minimum players in team"
#define KEY_REQUIRED_TEAMS_COUNT "required teams count"
#define KEY_REQUIRED_JUNIORS "requires juniors"
#define KEY_ROUND_MATCHES "rounds matches"


// Singleton
class Personalization : public QObject
{
    Q_OBJECT

private:
    explicit Personalization(QObject *parent = nullptr);
    Personalization(const Personalization &) = delete; // rm copy constructor
    Personalization(      Personalization &&) = delete; // rm move constructor
    Personalization& operator=(const Personalization &) = delete; // rm copy operator
    Personalization& operator=(      Personalization &&) = delete; // rm move operator (y = std::move(x))
    ~Personalization();

public:
    static Personalization *const getInstance() noexcept;

    void setDefault();
    void load();

private:
    void save();

private:
    void computeRoundsCount();

public:
    /// Getters
    int getMinimumPlayersInTeam() const;
    int getRequiredTeamsCount() const;
    bool getRequiresJuniors() const;
    const QJsonObject &getRoundsMatches() const;
    const QJsonObject &getExampleData() const;
    int getRoundsCount() const;

signals:
    void loaded();
    void saved();
    void loadFailed();
    void saveFailed();

private:
    int m_minimumPlayersInTeam;
    int m_requiredTeamsCount;
    bool m_requiresJuniors;
    QJsonObject m_roundsMatches;
    QJsonObject m_exampleData;
    int m_roundsCount;
};

#endif // PERSONALIZATION_H
