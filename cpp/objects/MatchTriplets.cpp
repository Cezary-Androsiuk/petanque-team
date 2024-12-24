#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr)
{
    DOLT(this)

}

MatchTriplets::~MatchTriplets()
{
    DOLT(this)
}
