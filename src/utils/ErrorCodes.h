//
// Created by Jakub Gert on 21/06/2020.
//

#ifndef GRBL_ERRORCODES_H
#define GRBL_ERRORCODES_H

#include <QString>
#include <QMap>

struct ErrorCodeItem {
    unsigned int code;
    QString name;
    QString description;
};

class ErrorCodes {
    QMap<unsigned int, ErrorCodeItem> map;
private:
    bool load(const QString &fileName);

public:
    explicit ErrorCodes(const QString &fileName);

    ErrorCodeItem getErrorCodeItem(unsigned int code) const;
};

#endif //GRBL_ERRORCODES_H
