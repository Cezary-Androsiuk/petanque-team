#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>

#include "enums/GenderEnum.h"
#include "enums/AgeGroupEnum.h"
#include "Serializable.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_FIRST_NAME_KEY             "first name"
#define SERL_LAST_NAME_KEY              "last name"
#define SERL_LICENSE_KEY                "license"
#define SERL_AGE_GROUP_KEY              "age group"
#define SERL_GENDER_KEY                 "gender"
#define SERL_IS_TEAM_LEADER_KEY         "is team leader"
#define SERL_PLAYER_SMALL_POINTS_KEY    "small points"
#define SERL_PLAYER_LARGE_POINTS_KEY    "large points"

class Player : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(const QString &firstName READ getFirstName WRITE setFirstName NOTIFY firstNameChanged FINAL)
    Q_PROPERTY(const QString &lastName READ getLastName WRITE setLastName NOTIFY lastNameChanged FINAL)
    Q_PROPERTY(const QString &license READ getLicense WRITE setLicense NOTIFY licenseChanged FINAL)
    Q_PROPERTY(AgeGroupEnum ageGroup READ getAgeGroup WRITE setAgeGroup NOTIFY ageGroupChanged FINAL)
    Q_PROPERTY(GenderEnum gender READ getGender WRITE setGender NOTIFY genderChanged FINAL)
    Q_PROPERTY(bool isTeamLeader READ getIsTeamLeader WRITE setIsTeamLeader NOTIFY isTeamLeaderChanged FINAL)

public:
    explicit Player(QObject *parent = nullptr);
    ~Player();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jPlayer) override;

    void clear(bool emitting = true);

    void copyFromOtherPlayer(const Player &sourcePlayer);

public slots:
    /// EXAMPLE
    void assignExampleData(const QJsonObject &jPlayer);

public:
    /// GETTERS
    const QString &getFirstName() const;
    const QString &getLastName() const;
    const QString &getLicense() const;
    AgeGroupEnum getAgeGroup() const;
    GenderEnum getGender() const;
    bool getIsTeamLeader() const;
    int getSmallPoints() const;
    int getLargePoints() const;

    /// SETTERS
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setLicense(const QString &license);
    void setAgeGroup(AgeGroupEnum ageGroup);
    void setGender(GenderEnum gender);
    void setIsTeamLeader(bool isTeamLeader);
    void setSmallPoints(int smallPoints);
    void setLargePoints(int largePoints);

    /// MODIFIERS
    void addSmallPoints(int smallPoints);
    void addLargePoints(int largePoints);

signals:
    /// VARIABLE SIGNALS
    void firstNameChanged();
    void lastNameChanged();
    void licenseChanged();
    void ageGroupChanged();
    void genderChanged();
    void isTeamLeaderChanged();
    void smallPointsChanged();
    void largePointsChanged();

private:
    QString m_firstName;
    QString m_lastName;
    QString m_license;
    AgeGroupEnum m_ageGroup;
    GenderEnum m_gender;
    bool m_isTeamLeader;

    int m_smallPoints;
    int m_largePoints;
};

typedef QWeakPointer<Player> PlayerWPtr;
typedef QSharedPointer<Player> PlayerPtr;
typedef QList<PlayerPtr> PlayerPtrList;
typedef QVector<Player *> QmlPlayerPtrVector;

#endif // PLAYER_H
