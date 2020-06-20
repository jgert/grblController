//
// Created by Jakub Gert on 13/06/2020.
//

#include <QDebug>
#include <QLineEdit>
#include "LineEditItemDelegate.h"

LineEditItemDelegate::LineEditItemDelegate(QWidget *parent): QItemDelegate(parent) {

}

void LineEditItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const {
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

QWidget *LineEditItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {

    Q_UNUSED(index);
    Q_UNUSED(option);
    return new QLineEdit(parent);
}

void LineEditItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    auto lineEdit = dynamic_cast<QLineEdit*>(editor);
    auto variant = index.data(Qt::EditRole);
    auto text = variant.toString();
    lineEdit->setText(text);
    lineEdit->setPlaceholderText(text);
}

void LineEditItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

    auto lineEdit = dynamic_cast<QLineEdit*>(editor);
    model->setData(index, QVariant(lineEdit->text()));
}
