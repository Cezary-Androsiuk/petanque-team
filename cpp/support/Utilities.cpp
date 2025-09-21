#include "Utilities.h"
#include "Log.h"

Utilities::Utilities() {}

bool Utilities::isDateValid(QString stringDate, QString dateFormat)
{TRM;
    if(stringDate.isEmpty())
        return false;
    /// date format could be "yyyy-MM-dd"
    QDate date = QDate::fromString(stringDate, dateFormat);
    return date.isValid();
}
