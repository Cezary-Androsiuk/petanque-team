#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"
#include "cpp/Serializable.h"

/// KEYS FOR JSON - SERIALIZE AND DESERIALIZE PURPOSES
#define SERL_NAME_KEY       "name"
#define SERL_PLAYERS_KEY    "players"

class Team : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Team(QObject *parent = nullptr);

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &teamJson) override;

    void clear(bool emitting = true);

public slots:
    void createDetachedPlayer();
    void deleteDetachedPlayer();
    void addDetachedPlayer();

    void deletePlayer(int index);

public:
    QString getName() const;
    const PlayerPtr &getDetachedPlayer() const;
    const PlayerPtrList &getPlayers() const;

    void setName(QString name);

signals:
    void nameChanged();
    void playersChanged();
    void detachedPlayerChanged();

private:
    QString m_name;

    PlayerPtr m_detachedPlayer;
    PlayerPtrList m_players;
};

typedef QSharedPointer<Player> PlayerPtr;
typedef QList<PlayerPtr> PlayerPtrList;



#endif // TEAM_H
