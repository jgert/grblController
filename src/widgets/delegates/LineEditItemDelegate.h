//
// Created by Jakub Gert on 13/06/2020.
//

#ifndef GRBL_LINEEDITITEMDELEGATE_H
#define GRBL_LINEEDITITEMDELEGATE_H

#include <QItemDelegate>

class LineEditItemDelegate : public QItemDelegate {
Q_OBJECT
public:
    explicit LineEditItemDelegate(QWidget *parent = nullptr);

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void
    updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
};


#endif //GRBL_LINEEDITITEMDELEGATE_H
