#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>

#include "cpp/objects/Team.h"

class Match : public QObject
{
    Q_OBJECT
public:
    explicit Match(QObject *parent = nullptr);

signals:

private:
    TeamWPtr m_teamLeft;
    TeamWPtr m_teamRight;
};

typedef QSharedPointer<Match> MatchPtr;
typedef QList<MatchPtr> MatchPtrList;
typedef QVector<Match*> MatchPtrVectorQml;

#endif // MATCH_H
