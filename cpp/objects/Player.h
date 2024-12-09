#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/enums/GenderEnum.h"
#include "cpp/enums/AgeGroupEnum.h"
#include "cpp/Serializable.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_FIRST_NAME_KEY     "first name"
#define SERL_LAST_NAME_KEY      "last name"
#define SERL_LICENSE_KEY        "license"
#define SERL_AGE_GROUP_KEY      "age group"
#define SERL_GENDER_KEY         "gender"
#define SERL_IS_TEAM_LEADER_KEY "is team leader"

class Player : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName NOTIFY firstNameChanged FINAL)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName NOTIFY lastNameChanged FINAL)
    Q_PROPERTY(QString license READ getLicense WRITE setLicense NOTIFY licenseChanged FINAL)
    Q_PROPERTY(AgeGroupEnum ageGroup READ getAgeGroup WRITE setAgeGroup NOTIFY ageGroupChanged FINAL)
    Q_PROPERTY(GenderEnum gender READ getGender WRITE setGender NOTIFY genderChanged FINAL)
    Q_PROPERTY(bool isTeamLeader READ getIsTeamLeader WRITE setIsTeamLeader NOTIFY isTeamLeaderChanged FINAL)

public:
    explicit Player(QObject *parent = nullptr);
    ~Player();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &playerJson) override;

    void clear(bool emitting = true);

    void copyFromOtherPlayer(const Player &sourcePlayer);

private:

public:
    QString getFirstName() const;
    QString getLastName() const;
    QString getLicense() const;
    AgeGroupEnum getAgeGroup() const;
    GenderEnum getGender() const;
    bool getIsTeamLeader() const;

    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setLicense(const QString &license);
    void setAgeGroup(AgeGroupEnum ageGroup);
    void setGender(GenderEnum gender);
    void setIsTeamLeader(bool isTeamLeader);

signals:
    void firstNameChanged();
    void lastNameChanged();
    void licenseChanged();
    void ageGroupChanged();
    void genderChanged();
    void isTeamLeaderChanged();

private:
    QString m_firstName;
    QString m_lastName;
    QString m_license;
    AgeGroupEnum m_ageGroup;
    GenderEnum m_gender;
    bool m_isTeamLeader;
};

typedef QSharedPointer<Player> PlayerPtr;
typedef QList<PlayerPtr> PlayerPtrList;

#endif // PLAYER_H
