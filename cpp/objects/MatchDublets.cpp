#include "MatchDublets.h"

MatchDublets::MatchDublets(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : MatchTypeBase(tl, tr)
{
    DOLT(this)

}

    MatchDublets::~MatchDublets()
{
    DOLT(this)
}
