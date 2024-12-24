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
    explicit GroupSelection(QObject *parent = nullptr);
    ~GroupSelection();

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &jGroupSelection) override;

    void clear(bool emitting = true);

public:
    bool verify(QString &message);
    void setSelectionSize(qsizetype size);

public:
    void setGroupsCount(int groupsCount);
    void setMinPlayersInGroup(int minPlayersInGroup);
    void setMaxPlayersInGroup(int maxPlayersInGroup);

signals:

private:
    int m_groupsCount;
    int m_minPlayersInGroup;
    int m_maxPlayersInGroup;
    QList<int> m_playerSelections;

    static constexpr int defaultSelectionValue = -1;
};

typedef QSharedPointer<GroupSelection> GroupSelectionPtr;
typedef QList<GroupSelectionPtr> GroupSelectionPtrList;
typedef QVector<GroupSelection *> QmlGroupSelectionPtrVector;

#endif // GROUPSELECTION_H
