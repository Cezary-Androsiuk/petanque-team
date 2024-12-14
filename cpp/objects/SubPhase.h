#ifndef SUBPHASE_H
#define SUBPHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class SubPhase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
public:
    explicit SubPhase(QObject *parent = nullptr);
    ~SubPhase();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

    void clear();

public:
    QString getName() const;

    void setName(const QString &name);

signals:
    void nameChanged();

private:
    QString m_name;
};

typedef QSharedPointer<SubPhase> SubPhasePtr;
typedef QVector<SubPhasePtr> SubPhasePtrVector;
typedef QVector<SubPhase *> QmlSubPhasePtrVector;

#endif // SUBPHASE_H
