#include "serveralgotythms.h"

ServerAlgotythms::ServerAlgotythms() {}

bool ServerAlgotythms::isNameValid(QString name)
{
    if (name.length() > 20 || name.length() < 3)
        return false;
    // QRegularExpression r("[A-Za-z0-9_]+");
    QRegularExpression version(QRegularExpression::anchoredPattern(QString("[A-Za-z0-9_]+")));

    return version.match(name).hasMatch();
}
