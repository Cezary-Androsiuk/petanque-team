#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QObject>

class Serializable : public QObject
{
    Q_OBJECT
public:
    explicit Serializable(QObject *parent = nullptr);

signals:
};

#endif // SERIALIZABLE_H
