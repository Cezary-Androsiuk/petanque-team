#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/enums/Gender.h"
#include "cpp/enums/AgeGroup.h"

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fname READ getFname WRITE setFname NOTIFY fnameChanged FINAL)
    Q_PROPERTY(QString lname READ getLname WRITE setLname NOTIFY lnameChanged FINAL)
    Q_PROPERTY(QString license READ getLicense WRITE setLicense NOTIFY licenseChanged FINAL)
    Q_PROPERTY(AgeGroup ageGroup READ getAgeGroup WRITE setAgeGroup NOTIFY ageGroupChanged FINAL)
    Q_PROPERTY(Gender gender READ getGender WRITE setGender NOTIFY genderChanged FINAL)
    Q_PROPERTY(bool isTeamLeader READ getIsTeamLeader WRITE setIsTeamLeader NOTIFY isTeamLeaderChanged FINAL)

public:
    explicit Player(QObject *parent = nullptr);

    void copyFromOtherPlayer(const Player &sourcePlayer);

    QString getFname() const;
    QString getLname() const;
    QString getLicense() const;
    AgeGroup getAgeGroup() const;
    Gender getGender() const;
    bool getIsTeamLeader() const;

    void setFname(const QString &fname);
    void setLname(const QString &lname);
    void setLicense(const QString &license);
    void setAgeGroup(AgeGroup ageGroup);
    void setGender(Gender gender);
    void setIsTeamLeader(bool isTeamLeader);

signals:
    void fnameChanged();
    void lnameChanged();
    void licenseChanged();
    void ageGroupChanged();
    void genderChanged();
    void isTeamLeaderChanged();

private:
    QString m_fname;
    QString m_lname;
    QString m_license;
    AgeGroup m_ageGroup;
    Gender m_gender;
    bool m_isTeamLeader;
};

typedef QSharedPointer<Player> PlayerPtr;
typedef QList<PlayerPtr> PlayerPtrList;

#endif // PLAYER_H
