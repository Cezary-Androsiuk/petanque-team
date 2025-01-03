#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
    , m_ageGroup{AgeGroupEnum::Junior}
    , m_gender{GenderEnum::Male}
    , m_isTeamLeader{false}
{
    DOLT(this)
}

Player::~Player()
{
    DOLT(this)
}

QJsonObject Player::serialize() const
{
    /// save to json
    QJsonObject jPlayer;
    jPlayer[ SERL_FIRST_NAME_KEY ] = m_firstName;
    jPlayer[ SERL_LAST_NAME_KEY ] = m_lastName;
    jPlayer[ SERL_LICENSE_KEY ] = m_license;
    jPlayer[ SERL_AGE_GROUP_KEY ] = EnumConvert::AgeGroupToQString(m_ageGroup);
    jPlayer[ SERL_GENDER_KEY ] = EnumConvert::GenderToQString(m_gender);
    jPlayer[ SERL_IS_TEAM_LEADER_KEY ] = m_isTeamLeader;
    jPlayer[ SERL_PLAYER_SMALL_POINTS_KEY ] = m_smallPoints;
    jPlayer[ SERL_PLAYER_LARGE_POINTS_KEY ] = m_largePoints;

    return jPlayer;
}

void Player::deserialize(const QJsonObject &jPlayer)
{
    this->clear(false);

    /// read from json
    m_firstName = jPlayer[ SERL_FIRST_NAME_KEY ].toString();
    emit this->firstNameChanged();

    m_lastName = jPlayer[ SERL_LAST_NAME_KEY ].toString();
    emit this->lastNameChanged();

    m_license = jPlayer[ SERL_LICENSE_KEY ].toString();
    emit this->licenseChanged();

    QString ageGroupStr = jPlayer[ SERL_AGE_GROUP_KEY ].toString();
    m_ageGroup = EnumConvert::QStringToAgeGroup( ageGroupStr );
    emit this->ageGroupChanged();

    QString genderStr = jPlayer[ SERL_GENDER_KEY ].toString();
    m_gender = EnumConvert::QStringToGender( genderStr );
    emit this->genderChanged();

    m_isTeamLeader = jPlayer[ SERL_IS_TEAM_LEADER_KEY ].toBool();
    emit this->isTeamLeaderChanged();

    m_smallPoints = jPlayer[ SERL_PLAYER_SMALL_POINTS_KEY ].toInt();
    emit this->smallPointsChanged();

    m_largePoints = jPlayer[ SERL_PLAYER_LARGE_POINTS_KEY ].toInt();
    emit this->largePointsChanged();
}

void Player::clear(bool emitting)
{
    m_firstName.clear();
    if(emitting) emit this->firstNameChanged();

    m_lastName.clear();
    if(emitting) emit this->lastNameChanged();

    m_license.clear();
    if(emitting) emit this->licenseChanged();

    m_ageGroup = AgeGroupEnum::Junior;
    if(emitting) emit this->ageGroupChanged();

    m_gender = GenderEnum::Male;
    if(emitting) emit this->genderChanged();

    m_isTeamLeader = false;
    if(emitting) emit this->isTeamLeaderChanged();

    m_smallPoints = 0;
    if(emitting) emit this->smallPointsChanged();

    m_largePoints = 0;
    if(emitting) emit this->largePointsChanged();
}

void Player::copyFromOtherPlayer(const Player &sourcePlayer)
{
    if(this == &sourcePlayer)
    {
        W("trying to copy data from itself")
        return;
    }

    m_firstName = sourcePlayer.m_firstName;
    m_lastName = sourcePlayer.m_lastName;
    m_license = sourcePlayer.m_license;
    m_ageGroup = sourcePlayer.m_ageGroup;
    m_gender = sourcePlayer.m_gender;
    m_isTeamLeader = sourcePlayer.m_isTeamLeader;
    m_smallPoints = sourcePlayer.m_smallPoints;
    m_largePoints = sourcePlayer.m_largePoints;

    emit this->firstNameChanged();
    emit this->lastNameChanged();
    emit this->licenseChanged();
    emit this->ageGroupChanged();
    emit this->genderChanged();
    emit this->isTeamLeaderChanged();
    emit this->smallPointsChanged();
    emit this->largePointsChanged();
}

void Player::assignExampleData(const QJsonObject &jPlayer)
{
    m_firstName = jPlayer["first name"].toString();
    m_lastName = jPlayer["last name"].toString();
    m_license = jPlayer["license"].toString();
    m_ageGroup = EnumConvert::QStringToAgeGroup(jPlayer["age group"].toString());
    m_gender = EnumConvert::QStringToGender(jPlayer["gender"].toString());
    m_isTeamLeader = jPlayer["is team leader"].toBool();
}

const QString &Player::getFirstName() const
{
    return m_firstName;
}

const QString &Player::getLastName() const
{
    return m_lastName;
}

const QString &Player::getLicense() const
{
    return m_license;
}

AgeGroupEnum Player::getAgeGroup() const
{
    return m_ageGroup;
}

GenderEnum Player::getGender() const
{
    return m_gender;
}

bool Player::getIsTeamLeader() const
{
    return m_isTeamLeader;
}

int Player::getSmallPoints() const
{
    return m_smallPoints;
}

int Player::getLargePoints() const
{
    return m_largePoints;
}

void Player::setFirstName(const QString &firstName)
{
    if (m_firstName == firstName)
        return;
    m_firstName = firstName;
    emit firstNameChanged();
}

void Player::setLastName(const QString &lastName)
{
    if (m_lastName == lastName)
        return;
    m_lastName = lastName;
    emit lastNameChanged();
}

void Player::setLicense(const QString &license)
{
    if (m_license == license)
        return;
    m_license = license;
    emit licenseChanged();
}

void Player::setAgeGroup(AgeGroupEnum ageGroup)
{
    if (m_ageGroup == ageGroup)
        return;
    m_ageGroup = ageGroup;
    emit ageGroupChanged();
}

void Player::setGender(GenderEnum gender)
{
    if (m_gender == gender)
        return;
    m_gender = gender;
    emit genderChanged();
}

void Player::setIsTeamLeader(bool isTeamLeader)
{
    if (m_isTeamLeader == isTeamLeader)
        return;
    m_isTeamLeader = isTeamLeader;
    emit isTeamLeaderChanged();
}

void Player::setSmallPoints(int smallPoints)
{
    if(m_smallPoints == smallPoints)
        return;

    m_smallPoints = smallPoints;
    emit this->smallPointsChanged();
}

void Player::setLargePoints(int largePoints)
{
    if(m_largePoints == largePoints)
        return;

    m_largePoints = largePoints;
    emit this->largePointsChanged();
}

void Player::addSmallPoints(int smallPoints)
{
    if(smallPoints <= 0)
        return;

    m_smallPoints += smallPoints;
    emit this->smallPointsChanged();
}

void Player::addLargePoints(int largePoints)
{
    if(largePoints <= 0)
        return;

    m_largePoints += largePoints;
    emit this->largePointsChanged();
}
