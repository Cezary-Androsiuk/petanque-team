#include "MatchSingles.h"

#include "support/Log.h"

MatchSingles::MatchSingles(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr,
                    SINGLES_GROUPS_COUNT,
                    SINGLES_MIN_PLAYERS_IN_GROUP,
                    SINGLES_MAX_PLAYERS_IN_GROUP, parent)
{TRM; DOLTV(SAPF("%p, %p, %p", tl.lock().data(), tr.lock().data(), parent));

}

MatchSingles::~MatchSingles()
{TRM; DOLT;

}
