#ifndef MATCHDUBLETS_H
#define MATCHDUBLETS_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchTypeBase.h"

class MatchDublets : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchDublets(QObject *parent = nullptr);

signals:
};

typedef QSharedPointer<MatchDublets> MatchDubletsPtr;

#endif // MATCHDUBLETS_H
