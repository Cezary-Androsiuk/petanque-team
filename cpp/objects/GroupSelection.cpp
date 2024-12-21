#include "GroupSelection.h"

GroupSelection::GroupSelection(QObject *parent)
    : QObject{parent}
{
    DOLT(this);
}

GroupSelection::~GroupSelection()
{
    DOLT(this);
}

QJsonObject GroupSelection::serialize() const
{
    return QJsonObject();
}

void GroupSelection::deserialize(const QJsonObject &jGroupSelection)
{
    this->clear(false);
}

void GroupSelection::clear(bool emitting)
{

}
