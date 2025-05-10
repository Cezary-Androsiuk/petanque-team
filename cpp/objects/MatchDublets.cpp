#include "MatchDublets.h"

#include "support/Log.h"

MatchDublets::MatchDublets(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr,
                    DUBLETS_GROUPS_COUNT,
                    DUBLETS_MIN_PLAYERS_IN_GROUP,
                    DUBLETS_MAX_PLAYERS_IN_GROUP, parent)
{
    DOLT(this)

}

    MatchDublets::~MatchDublets()
{
    DOLT(this)
}
