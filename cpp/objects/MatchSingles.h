#ifndef MATCHSINGLES_H
#define MATCHSINGLES_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "objects/MatchTypeBase.h"

#define SINGLES_GROUPS_COUNT 6
#define SINGLES_MIN_PLAYERS_IN_GROUP 1
#define SINGLES_MAX_PLAYERS_IN_GROUP 1

class MatchSingles : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchSingles(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    ~MatchSingles();

signals:
};

typedef QSharedPointer<MatchSingles> MatchSinglesPtr;

#endif // MATCHSINGLES_H
