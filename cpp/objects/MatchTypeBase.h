#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>

class MatchTypeBase : public QObject
{
    Q_OBJECT
public:
    explicit MatchTypeBase(QObject *parent = nullptr);

signals:
};

#endif // MATCHTYPEBASE_H
