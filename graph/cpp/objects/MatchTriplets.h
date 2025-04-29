#ifndef MATCHTRIPLETS_H
#define MATCHTRIPLETS_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchTypeBase.h"

#define TRIPLETS_GROUPS_COUNT 2
#define TRIPLETS_MIN_PLAYERS_IN_GROUP 3
#define TRIPLETS_MAX_PLAYERS_IN_GROUP 4

class MatchTriplets : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchTriplets(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    ~MatchTriplets();

signals:
};

typedef QSharedPointer<MatchTriplets> MatchTripletsPtr;

#endif // MATCHTRIPLETS_H
