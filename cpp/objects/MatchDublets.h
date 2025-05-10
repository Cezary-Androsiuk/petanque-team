#ifndef MATCHDUBLETS_H
#define MATCHDUBLETS_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "objects/MatchTypeBase.h"

#define DUBLETS_GROUPS_COUNT 3
#define DUBLETS_MIN_PLAYERS_IN_GROUP 2
#define DUBLETS_MAX_PLAYERS_IN_GROUP 3

class MatchDublets : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchDublets(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    ~MatchDublets();

signals:
};

typedef QSharedPointer<MatchDublets> MatchDubletsPtr;

#endif // MATCHDUBLETS_H
