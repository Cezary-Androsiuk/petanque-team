#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>

#include "objects/Player.h"
#include "Serializable.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_TEAM_NAME_KEY          "name"
#define SERL_TEAM_SMALL_POINTS_KEY  "small points"
#define SERL_TEAM_LARGE_POINTS_KEY  "large points"
#define SERL_PLAYERS_KEY            "players"

class Team : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(Player *detachedPlayer READ getDetachedPlayerQml NOTIFY detachedPlayerChanged FINAL)
    Q_PROPERTY(QmlPlayerPtrVector players READ getPlayersQml NOTIFY playersChanged FINAL)
    Q_PROPERTY(int smallPoints READ getSmallPoints NOTIFY smallPointsChanged FINAL)
    Q_PROPERTY(int largePoints READ getLargePoints NOTIFY largePointsChanged FINAL)

public:
    explicit Team(QObject *parent = nullptr);
    ~Team();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jTeam) override;

    void clear(bool emitting = true);

public slots:
    void createDetachedPlayer();
    void deleteDetachedPlayer();
    void validateDetachedPlayer();
    void addDetachedPlayer();

    void deletePlayer(int index);

    /// EXAMPLE
    void assignExampleData(const QJsonObject &jTeam);

    /// SUPPORT
    void uncheckAllLeaders();

public:
    /// GETTERS
    const QString &getName() const;
    const PlayerPtr &getDetachedPlayer() const;
    const PlayerPtrList &getPlayers() const;
    int getSmallPoints() const;
    int getLargePoints() const;

    /// SETTERS
    void setName(const QString &name);
    void setSmallPoints(int smallPoints);
    void setLargePoints(int largePoints);

    /// MODIFIERS
    void addSmallPoints(int smallPoints);
    void addLargePoints(int largePoints);

    /// QML LIST GETTERS
    Player *getDetachedPlayerQml() const;
    QmlPlayerPtrVector getPlayersQml() const;

signals:
    /// VARIABLE SIGNALS
    void nameChanged();
    void detachedPlayerChanged();
    void playersChanged();
    void smallPointsChanged();
    void largePointsChanged();

    /// PLAYERS SIGNALS
    void detachedPlayerIsValid();
    void detachedPlayerValidationFailed(QString message);

private:
    QString m_name;

    int m_smallPoints;
    int m_largePoints;

    PlayerPtr m_detachedPlayer;
    PlayerPtrList m_players;
};

typedef QWeakPointer<Team> TeamWPtr;
typedef QSharedPointer<Team> TeamPtr;
typedef QList<TeamPtr> TeamPtrList;
typedef QVector<Team *> QmlTeamPtrVector;

#endif // TEAM_H
