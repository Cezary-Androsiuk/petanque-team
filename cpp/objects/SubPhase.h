#ifndef SUBPHASE_H
#define SUBPHASE_H

#include <QObject>

class SubPhase : public QObject
{
    Q_OBJECT
public:
    explicit SubPhase(QObject *parent = nullptr);

signals:
};

#endif // SUBPHASE_H
