#ifndef TEAM_H
#define TEAM_H

#include <QObject>

#include "cpp/objects/Player.h"

class Team : public QObject
{
    Q_OBJECT
public:
    explicit Team(QObject *parent = nullptr);

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

#endif // TEAM_H
