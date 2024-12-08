#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
    , m_ageGroup{AgeGroup::Junior}
    , m_gender{Gender::Male}
    , m_isTeamLeader{false}
{}

QJsonObject Player::serialize() const
{
    /// save to json
    QJsonObject playerJson;
    playerJson[ SERL_FIRST_NAME_KEY ] = m_firstName;
    playerJson[ SERL_LAST_NAME_KEY ] = m_lastName;
    playerJson[ SERL_LICENSE_KEY ] = m_license;
    playerJson[ SERL_AGE_GROUP_KEY ] = EnumConvert::AgeGroupToQString(m_ageGroup);
    playerJson[ SERL_GENDER_KEY ] = EnumConvert::GenderToQString(m_gender);
    playerJson[ SERL_IS_TEAM_LEADER_KEY ] = m_isTeamLeader;

    return playerJson;
}

void Player::deserialize(const QJsonObject &playerJson)
{
    /// read from json
    m_firstName = playerJson[ SERL_FIRST_NAME_KEY ].toString();
    m_lastName = playerJson[ SERL_LAST_NAME_KEY ].toString();
    m_license = playerJson[ SERL_LICENSE_KEY ].toString();
    QString ageGroupStr = playerJson[ SERL_AGE_GROUP_KEY ].toString();
    m_ageGroup = EnumConvert::QStringToAgeGroup( ageGroupStr );
    QString genderStr = playerJson[ SERL_GENDER_KEY ].toString();
    m_gender = EnumConvert::QStringToGender( genderStr );
    m_isTeamLeader = playerJson[ SERL_IS_TEAM_LEADER_KEY ].toBool();
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

    emit this->firstNameChanged();
    emit this->lastNameChanged();
    emit this->licenseChanged();
    emit this->ageGroupChanged();
    emit this->genderChanged();
    emit this->isTeamLeaderChanged();
}

QString Player::getFirstName() const
{
    return m_firstName;
}

QString Player::getLastName() const
{
    return m_lastName;
}

QString Player::getLicense() const
{
    return m_license;
}

AgeGroup Player::getAgeGroup() const
{
    return m_ageGroup;
}

Gender Player::getGender() const
{
    return m_gender;
}

bool Player::getIsTeamLeader() const
{
    return m_isTeamLeader;
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

void Player::setAgeGroup(AgeGroup ageGroup)
{
    if (m_ageGroup == ageGroup)
        return;
    m_ageGroup = ageGroup;
    emit ageGroupChanged();
}

void Player::setGender(Gender gender)
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
