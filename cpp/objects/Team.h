#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/storages/Personalization.h"
#include "cpp/objects/Player.h"
#include "cpp/Serializable.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_TEAM_NAME_KEY  "name"
#define SERL_PLAYERS_KEY    "players"

class Team : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(Player *detachedPlayer READ getDetachedPlayerQml NOTIFY detachedPlayerChanged FINAL)
    Q_PROPERTY(QmlPlayerPtrVector players READ getPlayersQml NOTIFY playersChanged FINAL)

public:
    explicit Team(QObject *parent = nullptr);
    ~Team();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &teamJson) override;

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

    /// SETTERS
    void setName(const QString &name);

    /// QML LIST GETTERS
    Player *getDetachedPlayerQml() const;
    QmlPlayerPtrVector getPlayersQml() const;

signals:
    /// VARIABLE SIGNALS
    void nameChanged();
    void detachedPlayerChanged();
    void playersChanged();

    /// PLAYERS SIGNALS
    void detachedPlayerIsValid();
    void detachedPlayerValidationFailed(QString message);

private:
    QString m_name;

    PlayerPtr m_detachedPlayer;
    PlayerPtrList m_players;
};

typedef QSharedPointer<Team> TeamPtr;
typedef QList<TeamPtr> TeamPtrList;
typedef QVector<Team *> QmlTeamPtrVector;



#endif // TEAM_H
