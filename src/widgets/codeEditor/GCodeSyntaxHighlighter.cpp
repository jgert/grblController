//
// Created by Jakub Gert on 05/10/2020.
//

#include <QDebug>
#include "GCodeSyntaxHighlighter.h"
#include "src/gCode/Parser.h"

void GCodeSyntaxHighlighter::highlightBlock(const QString &text) {
    auto parser = gCode::Parser();

    parser.parse(text.toStdString());

    for (auto const &block: parser.blocks()) {
        for (auto const &chunk: block.chunks) {
            QTextCharFormat *format(nullptr);

            format = formatters[chunk.type];

            if (format != nullptr) {
                setFormat(chunk.startPosition, chunk.length, *format);
            }
        }
    }
}

GCodeSyntaxHighlighter::GCodeSyntaxHighlighter(QTextDocument *pDocument) :
        QSyntaxHighlighter(pDocument) {


    QTextCharFormat *formatter;

    formatter = new QTextCharFormat();
    formatter->setFontWeight(QFont::ExtraBold);
    formatter->setForeground(Qt::red);
    formatters[gCode::Chunk::Type::Error] = formatter;

    formatter = new QTextCharFormat();
    formatter->setFontWeight(QFont::Bold);
    formatter->setForeground(Qt::darkMagenta);
    formatters[gCode::Chunk::Type::Percent] = formatter;

    formatter = new QTextCharFormat();
    formatter->setFontWeight(QFont::ExtraBold);
    formatter->setForeground(Qt::darkMagenta);
    formatters[gCode::Chunk::Type::Command] = formatter;
    formatters[gCode::Chunk::Type::M] = formatter;
    formatters[gCode::Chunk::Type::Tool] = formatter;

    formatter = new QTextCharFormat();
    formatter->setFontWeight(QFont::ExtraLight);
    formatter->setForeground(Qt::lightGray);
    formatters[gCode::Chunk::Type::LineNumber] = formatter;

    formatter = new QTextCharFormat();
    formatter->setFontWeight(QFont::Medium);
    formatter->setForeground(Qt::darkGreen);
    formatters[gCode::Chunk::Type::Address] = formatter;

    formatter = new QTextCharFormat();
    formatter->setFontWeight(QFont::ExtraLight);
    formatter->setForeground(Qt::lightGray);
    formatter->setFontItalic(true);
}
