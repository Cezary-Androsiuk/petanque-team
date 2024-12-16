#ifndef MATCHTRIPLETS_H
#define MATCHTRIPLETS_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchTypeBase.h"

class MatchTriplets : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchTriplets(QObject *parent = nullptr);
    ~MatchTriplets();

signals:
};

typedef QSharedPointer<MatchTriplets> MatchTripletsPtr;

#endif // MATCHTRIPLETS_H
