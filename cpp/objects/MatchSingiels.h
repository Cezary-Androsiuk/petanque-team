#ifndef MATCHSINGIELS_H
#define MATCHSINGIELS_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchTypeBase.h"

class MatchSingiels : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchSingiels(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent = nullptr);
    ~MatchSingiels();

signals:
};

typedef QSharedPointer<MatchSingiels> MatchSingielsPtr;

#endif // MATCHSINGIELS_H
