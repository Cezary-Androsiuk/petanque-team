#ifndef SUBPHASE_H
#define SUBPHASE_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Round.h"

typedef QVector<QPair<int, int>> IntPairs;

class SubPhase : public QObject, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
public:
    explicit SubPhase(int roundsCount, QObject *parent = nullptr);
    ~SubPhase();

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &data) override;

    void clear();

public:
    bool verify(QString &message) const;
    bool hasNextRound() const;
    void goToNextRound();

public:
    QString getName() const;

    void setName(const QString &name);

signals:
    void nameChanged();

private:
    QString m_name;
    int m_currentRound;
    RoundPtrVector m_rounds;
};

typedef QSharedPointer<SubPhase> SubPhasePtr;
typedef QVector<SubPhasePtr> SubPhasePtrVector;
typedef QVector<SubPhase *> QmlSubPhasePtrVector;

#endif // SUBPHASE_H
