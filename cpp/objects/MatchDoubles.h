#ifndef MATCHDOUBLES_H
#define MATCHDOUBLES_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "objects/MatchTypeBase.h"

#define DOUBLES_GROUPS_COUNT 3
#define DOUBLES_MIN_PLAYERS_IN_GROUP 2
#define DOUBLES_MAX_PLAYERS_IN_GROUP 3

class MatchDoubles : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchDoubles(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    ~MatchDoubles();

signals:
};

typedef QSharedPointer<MatchDoubles> MatchDoublesPtr;

#endif // MATCHDOUBLES_H
