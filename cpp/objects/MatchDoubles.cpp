#include "MatchDoubles.h"

#include "support/Log.h"

MatchDoubles::MatchDoubles(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr,
                    DOUBLES_GROUPS_COUNT,
                    DOUBLES_MIN_PLAYERS_IN_GROUP,
                    DOUBLES_MAX_PLAYERS_IN_GROUP, parent)
{TRM; DOLTV(SAPF("%p, %p, %p", tl.lock().data(), tr.lock().data(), parent));

}

MatchDoubles::~MatchDoubles()
{TRM; DOLT;

}
