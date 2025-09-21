#ifndef UTILITIES_H
#define UTILITIES_H

#include <QDate>
#include <QString>

class Utilities
{
public:
    Utilities();

    static bool isDateValid(QString date, QString dateFormat);
};

#endif // UTILITIES_H
