#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr,
                    TRIPLETS_GROUPS_COUNT,
                    TRIPLETS_MIN_PLAYERS_IN_GROUP,
                    TRIPLETS_MAX_PLAYERS_IN_GROUP, parent)
{
    DOLT(this)

}

MatchTriplets::~MatchTriplets()
{
    DOLT(this)
}
