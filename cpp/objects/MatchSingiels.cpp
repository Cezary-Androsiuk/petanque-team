#include "MatchSingiels.h"

MatchSingiels::MatchSingiels(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr)
{
    DOLT(this)
}

MatchSingiels::~MatchSingiels()
{
    DOLT(this)
}
