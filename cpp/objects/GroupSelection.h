#ifndef GROUPSELECTION_H
#define GROUPSELECTION_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "cpp/support/Log.h"
#include "cpp/Serializable.h"
#include "cpp/objects/Team.h"

class GroupSelection : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit GroupSelection(uint groupsCount, uint minPlayersInGroup, uint maxPlayersInGroup, QObject *parent = nullptr);
    ~GroupSelection();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupSelection) override;

    void clear(bool emitting = true);

public:
    bool verify(QString &message);
    void setSelectionSize(qsizetype size);

signals:

private:
    const uint m_groupsCount;
    const uint m_minPlayersInGroup;
    const uint m_maxPlayersInGroup;
    QList<int> m_playerSelections;

    static constexpr int defaultSelectionValue = -1;
};

typedef QSharedPointer<GroupSelection> GroupSelectionPtr;
typedef QList<GroupSelectionPtr> GroupSelectionPtrList;
typedef QVector<GroupSelection *> QmlGroupSelectionPtrVector;

#endif // GROUPSELECTION_H
