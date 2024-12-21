#ifndef GROUPSELECTION_H
#define GROUPSELECTION_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"

class GroupSelection : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit GroupSelection(QObject *parent = nullptr);
    ~GroupSelection();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupSelection) override;

    void clear(bool emitting = true);

signals:

private:

};

typedef QSharedPointer<GroupSelection> GroupSelectionPtr;
typedef QList<GroupSelectionPtr> GroupSelectionPtrList;
typedef QVector<GroupSelection *> QmlGroupSelectionPtrVector;

#endif // GROUPSELECTION_H
