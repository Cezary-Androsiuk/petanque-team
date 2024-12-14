#include "SubPhase.h"

SubPhase::SubPhase(QObject *parent)
    : QObject{parent}
{
    I(QAPF("Creating SubPhase: %p", this));
}

SubPhase::~SubPhase()
{
    I(QAPF("Destroying SubPhase: %p", this));
}

QJsonObject SubPhase::serialize() const
{
    return QJsonObject();
}

void SubPhase::deserialize(const QJsonObject &data)
{

}

void SubPhase::clear()
{

}

QString SubPhase::getName() const
{
    return m_name;
}

void SubPhase::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
