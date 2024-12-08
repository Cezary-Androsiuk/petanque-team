#ifndef SUBPHASE_H
#define SUBPHASE_H

#include <QObject>

class SubPhase : public QObject
{
    Q_OBJECT
public:
    explicit SubPhase(QObject *parent = nullptr);

    // QJsonObject serialize() const override;
    // void deserialize(const QJsonObject &data) override;

    // void clear();

signals:
};

#endif // SUBPHASE_H
