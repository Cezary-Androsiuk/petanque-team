#ifndef MATCHTRIPLES_H
#define MATCHTRIPLES_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "objects/MatchTypeBase.h"

#define TRIPLES_GROUPS_COUNT 2
#define TRIPLES_MIN_PLAYERS_IN_GROUP 3
#define TRIPLES_MAX_PLAYERS_IN_GROUP 4

class MatchTriples : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchTriples(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    ~MatchTriples();

signals:
};

typedef QSharedPointer<MatchTriples> MatchTriplesPtr;

#endif // MATCHTRIPLES_H
