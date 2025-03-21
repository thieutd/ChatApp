/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_ROOM_H_
#define _CLIENTMODELS_ROOM_H_

#include "../include/RoomType.gen.h"

class RoomMembership;
class Message;

class CLIENTMODELS_EXPORT Room : public qx::IxPersistable
{

   QX_REGISTER_FRIEND_CLASS(Room)

   QX_PERSISTABLE_HPP(Room)

public:

   typedef qx::QxCollection<QPair<quint64,quint64>, std::shared_ptr<RoomMembership> > type_list_of_room_membership;
   typedef qx::QxCollection<quint64, std::shared_ptr<Message> > type_list_of_message;

protected:

   quint64 m_id;
   QString m_name;
   RoomType::enum_RoomType m_type;
   QString m_description;
   QString m_avatar_url;
   QDateTime m_created_at;
   bool m_is_deleted;
   qint64 m_last_message_id;
   QDateTime m_last_synced;
   type_list_of_room_membership m_list_of_room_membership;
   type_list_of_message m_list_of_message;

public:

   Room();
   Room(const quint64 & id);
   virtual ~Room();

   quint64 getid() const;
   QString getname() const;
   RoomType::enum_RoomType gettype() const;
   QString getdescription() const;
   QString getavatar_url() const;
   QDateTime getcreated_at() const;
   bool getis_deleted() const;
   qint64 getlast_message_id() const;
   QDateTime getlast_synced() const;
   type_list_of_room_membership getlist_of_room_membership() const;
   type_list_of_room_membership & list_of_room_membership();
   const type_list_of_room_membership & list_of_room_membership() const;
   type_list_of_message getlist_of_message() const;
   type_list_of_message & list_of_message();
   const type_list_of_message & list_of_message() const;

   void setid(const quint64 & val);
   void setname(const QString & val);
   void settype(const RoomType::enum_RoomType & val);
   void setdescription(const QString & val);
   void setavatar_url(const QString & val);
   void setcreated_at(const QDateTime & val);
   void setis_deleted(const bool & val);
   void setlast_message_id(const qint64 & val);
   void setlast_synced(const QDateTime & val);
   void setlist_of_room_membership(const type_list_of_room_membership & val);
   void setlist_of_message(const type_list_of_message & val);

   type_list_of_room_membership getlist_of_room_membership(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_room_membership & list_of_room_membership(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_message getlist_of_message(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_message & list_of_message(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_list_of_room_membership(bool key = false) { Q_UNUSED(key); return "list_of_room_membership"; }
   static QString relation_list_of_message(bool key = false) { Q_UNUSED(key); return "list_of_message"; }

public:

   static QString column_id(bool key = false) { Q_UNUSED(key); return "id"; }
   static QString column_name(bool key = false) { Q_UNUSED(key); return "name"; }
   static QString column_type(bool key = false) { Q_UNUSED(key); return "type"; }
   static QString column_description(bool key = false) { Q_UNUSED(key); return "description"; }
   static QString column_avatar_url(bool key = false) { Q_UNUSED(key); return "avatar_url"; }
   static QString column_created_at(bool key = false) { Q_UNUSED(key); return "created_at"; }
   static QString column_is_deleted(bool key = false) { Q_UNUSED(key); return "is_deleted"; }
   static QString column_last_message_id(bool key = false) { Q_UNUSED(key); return "last_message_id"; }
   static QString column_last_synced(bool key = false) { Q_UNUSED(key); return "last_synced"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("Room") : QString("room")); }

};

typedef std::shared_ptr<Room> Room_ptr;
typedef qx::QxCollection<quint64, Room_ptr> list_of_Room;
typedef std::shared_ptr<list_of_Room> list_of_Room_ptr;

QX_REGISTER_PRIMARY_KEY(Room, quint64)
QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CLIENTMODELS(Room, qx::trait::no_base_class_defined, 0, Room)

#include "../include/RoomMembership.gen.h"
#include "../include/Message.gen.h"

#include "../custom/include/Room.h"

#endif // _CLIENTMODELS_ROOM_H_
