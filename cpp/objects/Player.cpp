#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
    , m_ageGroup{AgeGroup::Junior}
    , m_gender{Gender::Male}
    , m_isTeamLeader{false}
{}

void Player::copyFromOtherPlayer(const Player &sourcePlayer)
{
    if(this == &sourcePlayer)
    {
        W("trying to copy data from itself")
        return;
    }

    m_fname = sourcePlayer.m_fname;
    m_lname = sourcePlayer.m_lname;
    m_license = sourcePlayer.m_license;
    m_ageGroup = sourcePlayer.m_ageGroup;
    m_gender = sourcePlayer.m_gender;
    m_isTeamLeader = sourcePlayer.m_isTeamLeader;

    emit this->fnameChanged();
    emit this->lnameChanged();
    emit this->licenseChanged();
    emit this->ageGroupChanged();
    emit this->genderChanged();
    emit this->isTeamLeaderChanged();
}

QString Player::getFname() const
{
    return m_fname;
}

QString Player::getLname() const
{
    return m_lname;
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

void Player::setFname(const QString &fname)
{
    if (m_fname == fname)
        return;
    m_fname = fname;
    emit fnameChanged();
}

void Player::setLname(const QString &lname)
{
    if (m_lname == lname)
        return;
    m_lname = lname;
    emit lnameChanged();
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
