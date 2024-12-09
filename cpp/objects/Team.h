#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"
#include "cpp/Serializable.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_TEAM_NAME_KEY  "name"
#define SERL_PLAYERS_KEY    "players"

class Team : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(const Player *detachedPlayer READ getDetachedPlayerQml NOTIFY detachedPlayerChanged FINAL)
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
    void addDetachedPlayer();

    void deletePlayer(int index);

    /// EXAMPLE
    void createExamplePlayers();

public:
    /// GETTERS
    const QString &getName() const;
    const PlayerPtr &getDetachedPlayer() const;
    const PlayerPtrList &getPlayers() const;

    /// SETTERS
    void setName(const QString &name);

    /// QML LIST GETTERS
    const Player *getDetachedPlayerQml() const;
    QmlPlayerPtrVector getPlayersQml() const;

signals:
    void nameChanged();
    void detachedPlayerChanged();
    void playersChanged();

private:
    QString m_name;

    PlayerPtr m_detachedPlayer;
    PlayerPtrList m_players;
};

typedef QSharedPointer<Team> TeamPtr;
typedef QList<TeamPtr> TeamPtrList;
typedef QVector<const Team *> QmlTeamPtrVector;



#endif // TEAM_H
