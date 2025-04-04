#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include "typedefs.h"

#include <QStyledItemDelegate>

// struct MessageModel
// {
//     QString message;
//     UserIdType senderId;
// };

// class MessageDelegate : public QStyledItemDelegate
// {
// private:
//     UserIdType userId;

// public:
//     MessageDelegate(const UserIdType& userId, QObject* parent = nullptr)
//         : QStyledItemDelegate(parent)
//         , userId(userId)
//     {}

//     MessageDelegate(QObject* parent = nullptr)
//         : QStyledItemDelegate(parent)
//     {}

//     void setUser(const UserIdType& userId) { this->userId = userId; }

//     void paint(QPainter* painter,
//                const QStyleOptionViewItem& option,
//                const QModelIndex& index) const override
//     {
//         QStyleOptionViewItem opt = option;
//         initStyleOption(&opt, index);

//         UserIdType senderId = index.data(Qt::UserRole).value<UserIdType>();
//         opt.displayAlignment = (userId == senderId) ? Qt::AlignRight : Qt::AlignLeft;

//         QStyledItemDelegate::paint(painter, opt, index);
//     }

//     QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
//     {
//         QFontMetrics fm(option.font);
//         int lineHeight = fm.lineSpacing();
//         return QSize(option.rect.width(), lineHeight * 2);
//     }
// };

// class MessageDelegate : public QStyledItemDelegate
// {
//     Q_OBJECT
// public:
//     MessageDelegate(const UserIdType& userId, QObject* parent = nullptr)
//         : QStyledItemDelegate(parent)
//         , userId(userId)
//     {}

//     void paint(QPainter* painter,
//                const QStyleOptionViewItem& option,
//                const QModelIndex& index) const override
//     {
//         model_view::Message_model

//         QStyleOptionViewItem opt = option;
//         initStyleOption(&opt, index);

//         UserIdType senderId = index.data(Qt::UserRole).value<UserIdType>();
//         opt.displayAlignment = (userId == senderId) ? Qt::AlignRight : Qt::AlignLeft;

//         QStyledItemDelegate::paint(painter, opt, index);
//     }

// private:
//     UserIdType userId;
// };



#endif // MESSAGEDELEGATE_H
