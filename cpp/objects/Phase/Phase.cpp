#include "Phase.h"

Phase::Phase(QObject *parent)
    : QObject{parent}
{
    I(QAPF("Creating Phase: %p", this));
}

Phase::~Phase()
{
    I(QAPF("Destroying Phase: %p", this));
}
