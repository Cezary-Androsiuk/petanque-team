#include "Personalization.h"

#include "storages/DefaultPersonalizationData.h"

Personalization *Personalization::instance = nullptr;

Personalization::Personalization(QObject *parent)
    : QObject{parent}
{
    DOLT(this)
    this->setDefault();
    this->load();
}

Personalization::~Personalization()
{
    DOLT(this)
    this->save();
}

Personalization *Personalization::getInstance() noexcept
{
    // static Personalization p; /// lazy initialization
    return instance; /// handled by SingletonManager
}

void Personalization::setDefault()
{
    m_requiredTeamsCount = defaultRequiredTeamsCount;
    m_minimumPlayersInTeam = defaultMinimumPlayersInTeam;
    m_requiresJuniors = defaultRequiresJuniors;
    m_maxPointsInMatch = defaultMaxPointsInMatch;
    m_roundsMatches = QJsonDocument::fromJson(defaultRoundsMatches).object();
    this->computeRoundsCount();
    m_exampleData = QJsonDocument::fromJson(defaultExampleData).object();
}

void Personalization::load()
{
    // I("loading personalization");

    if(!QFile(JSON_FILE).exists()){
        MARK_ERROR("file " JSON_FILE " not found");
        emit this->loadFailed();
        return;
    }

    QFile jsonFile(JSON_FILE);
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        MARK_ERROR("Can not open personalization json file: " JSON_FILE);
        emit this->loadFailed();
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonData = QJsonDocument::fromJson(jsonFile.readAll(), &jsonError);
    jsonFile.close();

    if(jsonError.error != QJsonParseError::NoError) {
        MARK_ERROR("json parse error: " + jsonError.errorString());
        emit this->loadFailed();
        return;
    }

    if(!jsonData.isObject()){
        MARK_ERROR("json file does not contains json object");
        emit this->loadFailed();
        return;
    }

    // at this point data are default

    auto jp = jsonData.object();
    QString key;

    if(jp[KEY_PERSONALIZATION_VERSION].toInt() != personalizationVersion)
    {
        W("Personalization data version changed");
        W("After exiting the application new version will override personalization json file");
        W("Using new Default personalization data");

        /// do not read deprecated personalization file, exit method (use new default data)
        emit this->loaded();
        return;
    }

    /// try to load data, but if key is missing then, notify and leave default value
    key = KEY_MINIMUM_PLAYERS_IN_TEA;
    if(jp.contains(key)) m_minimumPlayersInTeam = jp[key].toInt();
    else KEY_NOT_FOUND_MESSAGE;

    key = KEY_REQUIRED_TEAMS_COUNT;
    if(jp.contains(key)) m_requiredTeamsCount = jp[key].toInt();
    else KEY_NOT_FOUND_MESSAGE;

    key = KEY_REQUIRED_JUNIORS;
    if(jp.contains(key)) m_requiresJuniors = jp[key].toBool();
    else KEY_NOT_FOUND_MESSAGE;

    key = KEY_MAX_POINTS_IN_MATCH;
    if(jp.contains(key)) m_maxPointsInMatch = jp[key].toInt();
    else KEY_NOT_FOUND_MESSAGE;

    key = KEY_ROUND_MATCHES;
    if(jp.contains(key)) m_roundsMatches = jp[key].toObject();
    else KEY_NOT_FOUND_MESSAGE;
    this->computeRoundsCount();

    key = KEY_EXAMPLE_DATA;
    if(jp.contains(key)) m_exampleData = jp[key].toObject();
    else KEY_NOT_FOUND_MESSAGE;

    I("personalization data loaded");

    emit this->loaded();
}

void Personalization::save()
{
    QJsonObject jsonObject;
    jsonObject[KEY_NOTE] = QString(DEFAULT_NOTE);
    jsonObject[KEY_PERSONALIZATION_VERSION] = personalizationVersion;

    jsonObject[KEY_MINIMUM_PLAYERS_IN_TEA] = this->getMinimumPlayersInTeam();
    jsonObject[KEY_REQUIRED_TEAMS_COUNT] = this->getRequiredTeamsCount();
    jsonObject[KEY_REQUIRED_JUNIORS] = this->getRequiresJuniors();
    jsonObject[KEY_MAX_POINTS_IN_MATCH] = this->getMaxPointsInMatch();
    jsonObject[KEY_ROUND_MATCHES] = this->getRoundsMatches();
    jsonObject[KEY_EXAMPLE_DATA] = this->getExampleData();

    QJsonDocument jsonData(jsonObject);

    QFile file(JSON_FILE);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        MARK_ERROR("error while saving json file to " JSON_FILE " with error " + file.errorString());
        emit this->saveFailed();
        return;
    }

    file.write(jsonData.toJson());
    file.close();

    I("personalization data saved", Log::Action::SavePrint); // Adding to session cause the process crash

    emit this->saved();
}

void Personalization::computeRoundsCount()
{
    m_roundsCount = m_roundsMatches.size();
        m_roundsCount++;
}


int Personalization::getMinimumPlayersInTeam() const
{
    return m_minimumPlayersInTeam;
}

int Personalization::getRequiredTeamsCount() const
{
    return m_requiredTeamsCount;
}

bool Personalization::getRequiresJuniors() const
{
    return m_requiresJuniors;
}

int Personalization::getMaxPointsInMatch() const
{
    return m_maxPointsInMatch;
}

const QJsonObject &Personalization::getRoundsMatches() const
{
    return m_roundsMatches;
}

const QJsonObject &Personalization::getExampleData() const
{
    return m_exampleData;
}

int Personalization::getRoundsCount() const
{
    return m_roundsCount;
}

