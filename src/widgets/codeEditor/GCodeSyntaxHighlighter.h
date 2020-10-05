//
// Created by Jakub Gert on 05/10/2020.
//

#ifndef GRBL_GCODESYNTAXHIGLIGHTER_H
#define GRBL_GCODESYNTAXHIGLIGHTER_H


#include <QSyntaxHighlighter>
#include "src/gCode/Parser.h"

class GCodeSyntaxHighlighter : public QSyntaxHighlighter {
Q_OBJECT
private:
    QMap<gCode::Chunk::Type, QTextCharFormat*> formatters;
public:
    explicit GCodeSyntaxHighlighter(QTextDocument *pDocument);

protected:
    void highlightBlock(const QString &text) override;
};


#endif //GRBL_GCODESYNTAXHIGLIGHTER_H
