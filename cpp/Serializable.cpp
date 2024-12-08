#include "Serializable.h"

Serializable::Serializable(QObject *parent)
    : QObject{parent}
{

}

Serializable::~Serializable() = default;
