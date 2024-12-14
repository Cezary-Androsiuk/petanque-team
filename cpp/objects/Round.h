#ifndef ROUND_H
#define ROUND_H

#include <QObject>

#include "cpp/objects/Match.h"

class Round : public QObject
{
    Q_OBJECT
public:
    explicit Round(QObject *parent = nullptr);

signals:

private:
    MatchPtrList m_matches;
};

#endif // ROUND_H
