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
    QJsonObject playerObject;
    playerObject[ SERL_FIRST_NAME_KEY ] = m_firstName;
    playerObject[ SERL_LAST_NAME_KEY ] = m_lastName;
    playerObject[ SERL_LICENSE_KEY ] = m_license;
    playerObject[ SERL_AGE_GROUP_KEY ] = EnumConvert::AgeGroupToQString(m_ageGroup);
    playerObject[ SERL_GENDER_KEY ] = EnumConvert::GenderToQString(m_gender);
    playerObject[ SERL_IS_TEAM_LEADER_KEY ] = m_isTeamLeader;

    return playerObject;
}

void Player::deserialize(const QJsonObject &data)
{
    /// read from json
    m_firstName = data[ SERL_FIRST_NAME_KEY ].toString();
    m_lastName = data[ SERL_LAST_NAME_KEY ].toString();
    m_license = data[ SERL_LICENSE_KEY ].toString();
    QString ageGroupStr = data[ SERL_AGE_GROUP_KEY ].toString();
    m_ageGroup = EnumConvert::QStringToAgeGroup( ageGroupStr );
    QString genderStr = data[ SERL_GENDER_KEY ].toString();
    m_gender = EnumConvert::QStringToGender( genderStr );
    m_isTeamLeader = data[ SERL_IS_TEAM_LEADER_KEY ].toBool();
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
