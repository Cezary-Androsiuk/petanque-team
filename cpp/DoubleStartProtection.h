#ifndef DOUBLESTARTPROTECTION_H
#define DOUBLESTARTPROTECTION_H

#include <QObject>
#include <QSharedMemory>

#define UNIQUE_KEY_PREVENT_DOUBLE_RUN "PetanqueTeam-IsRunning-mt9n8MSxmKiEUZo1"

class DoubleStartProtection : public QObject
{
    Q_OBJECT

public:
    explicit DoubleStartProtection(QObject *parent = nullptr);
    DoubleStartProtection(const DoubleStartProtection &) = delete; // rm copy constructor
    DoubleStartProtection(      DoubleStartProtection &&) = delete; // rm move constructor
    DoubleStartProtection& operator=(const DoubleStartProtection &) = delete; // rm copy operator
    DoubleStartProtection& operator=(      DoubleStartProtection &&) = delete; // rm move operator (y = std::move(x))
    ~DoubleStartProtection();

public slots:
    static DoubleStartProtection *const getInstance() noexcept;

    void verify() noexcept; /// start point

private:
    static bool testIfApplicationAlreadyRunning() noexcept; /// step, that if fail, cannot be retry

signals:
    void verified(); /// positive end

    void applicationIsAlreadyRunning(); /// negative end
};

#endif // DOUBLESTARTPROTECTION_H
