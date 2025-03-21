/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_MESSAGE_H_
#define _CLIENTMODELS_MESSAGE_H_

class User;
class Room;

class CLIENTMODELS_EXPORT Message : public qx::IxPersistable
{

   QX_REGISTER_FRIEND_CLASS(Message)

   QX_PERSISTABLE_HPP(Message)

public:

   typedef std::shared_ptr<User> type_user_id;
   typedef std::shared_ptr<Room> type_room_id;

protected:

   quint64 m_id;
   QString m_content;
   QDateTime m_created_at;
   bool m_is_deleted;
   bool m_is_sent;
   quint64 m_pending_id;
   QDateTime m_last_synced;
   type_user_id m_user_id;
   type_room_id m_room_id;

public:

   Message();
   Message(const quint64 & id);
   virtual ~Message();

   quint64 getid() const;
   QString getcontent() const;
   QDateTime getcreated_at() const;
   bool getis_deleted() const;
   bool getis_sent() const;
   quint64 getpending_id() const;
   QDateTime getlast_synced() const;
   type_user_id getuser_id() const;
   type_room_id getroom_id() const;

   void setid(const quint64 & val);
   void setcontent(const QString & val);
   void setcreated_at(const QDateTime & val);
   void setis_deleted(const bool & val);
   void setis_sent(const bool & val);
   void setpending_id(const quint64 & val);
   void setlast_synced(const QDateTime & val);
   void setuser_id(const type_user_id & val);
   void setroom_id(const type_room_id & val);

   type_user_id getuser_id(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_room_id getroom_id(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_user_id(bool key = false) { Q_UNUSED(key); return "user_id"; }
   static QString relation_room_id(bool key = false) { Q_UNUSED(key); return "room_id"; }

public:

   static QString column_id(bool key = false) { Q_UNUSED(key); return "id"; }
   static QString column_content(bool key = false) { Q_UNUSED(key); return "content"; }
   static QString column_created_at(bool key = false) { Q_UNUSED(key); return "created_at"; }
   static QString column_is_deleted(bool key = false) { Q_UNUSED(key); return "is_deleted"; }
   static QString column_is_sent(bool key = false) { Q_UNUSED(key); return "is_sent"; }
   static QString column_pending_id(bool key = false) { Q_UNUSED(key); return "pending_id"; }
   static QString column_last_synced(bool key = false) { Q_UNUSED(key); return "last_synced"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("Message") : QString("message")); }

};

typedef std::shared_ptr<Message> Message_ptr;
typedef qx::QxCollection<quint64, Message_ptr> list_of_Message;
typedef std::shared_ptr<list_of_Message> list_of_Message_ptr;

QX_REGISTER_PRIMARY_KEY(Message, quint64)
QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CLIENTMODELS(Message, qx::trait::no_base_class_defined, 0, Message)

#include "../include/User.gen.h"
#include "../include/Room.gen.h"

#include "../custom/include/Message.h"

#endif // _CLIENTMODELS_MESSAGE_H_
