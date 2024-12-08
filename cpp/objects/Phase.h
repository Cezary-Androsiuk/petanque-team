#ifndef PHASE_H
#define PHASE_H

#include <QObject>

#include "cpp/Serializable.h"

class Phase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Phase(QObject *parent = nullptr);
};

#endif // PHASE_H
