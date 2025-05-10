#include "MatchSingiels.h"

#include "support/Log.h"

MatchSingiels::MatchSingiels(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr,
                    SINGIELS_GROUPS_COUNT,
                    SINGIELS_MIN_PLAYERS_IN_GROUP,
                    SINGIELS_MAX_PLAYERS_IN_GROUP, parent)
{
    DOLT(this)
}

MatchSingiels::~MatchSingiels()
{
    DOLT(this)
}
