#include "MatchTriples.h"

#include "support/Log.h"

MatchTriples::MatchTriples(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr,
                    TRIPLES_GROUPS_COUNT,
                    TRIPLES_MIN_PLAYERS_IN_GROUP,
                    TRIPLES_MAX_PLAYERS_IN_GROUP, parent)
{TRM; DOLTV(SAPF("%p, %p, %p", tl.lock().data(), tr.lock().data(), parent));

}

MatchTriples::~MatchTriples()
{TRM; DOLT;

}
