#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>

class IconDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit IconDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.column() == 10) { // Edit icon column
            QPixmap penIcon(":/ressources/images/pen.png");
            painter->drawPixmap(option.rect.x() + 5, option.rect.y() + 5, 20, 20, penIcon);
        }
        else if (index.column() == 11) { // Delete icon column
            QPixmap binIcon(":/ressources/images/bin.png");
            painter->drawPixmap(option.rect.x() + 5, option.rect.y() + 5, 20, 20, binIcon);
        }
        else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};

#endif // ICONDELEGATE_H
