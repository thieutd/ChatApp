/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_USER_H_
#define _CLIENTMODELS_USER_H_

#include "../include/UserRole.gen.h"

class RoomMembership;
class Message;

class CLIENTMODELS_EXPORT User : public qx::IxPersistable
{

   QX_REGISTER_FRIEND_CLASS(User)

   QX_PERSISTABLE_HPP(User)

public:

   typedef qx::QxCollection<QPair<quint64,quint64>, std::shared_ptr<RoomMembership> > type_list_of_room_membership;
   typedef qx::QxCollection<quint64, std::shared_ptr<Message> > type_list_of_message;

protected:

   quint64 m_id;
   QString m_username;
   UserRole::enum_UserRole m_role;
   QString m_avatar_url;
   QDateTime m_created_at;
   bool m_is_deleted;
   QDateTime m_last_synced;
   type_list_of_room_membership m_list_of_room_membership;
   type_list_of_message m_list_of_message;

public:

   User();
   User(const quint64 & id);
   virtual ~User();

   quint64 getid() const;
   QString getusername() const;
   UserRole::enum_UserRole getrole() const;
   QString getavatar_url() const;
   QDateTime getcreated_at() const;
   bool getis_deleted() const;
   QDateTime getlast_synced() const;
   type_list_of_room_membership getlist_of_room_membership() const;
   type_list_of_room_membership & list_of_room_membership();
   const type_list_of_room_membership & list_of_room_membership() const;
   type_list_of_message getlist_of_message() const;
   type_list_of_message & list_of_message();
   const type_list_of_message & list_of_message() const;

   void setid(const quint64 & val);
   void setusername(const QString & val);
   void setrole(const UserRole::enum_UserRole & val);
   void setavatar_url(const QString & val);
   void setcreated_at(const QDateTime & val);
   void setis_deleted(const bool & val);
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
   static QString column_username(bool key = false) { Q_UNUSED(key); return "username"; }
   static QString column_role(bool key = false) { Q_UNUSED(key); return "role"; }
   static QString column_avatar_url(bool key = false) { Q_UNUSED(key); return "avatar_url"; }
   static QString column_created_at(bool key = false) { Q_UNUSED(key); return "created_at"; }
   static QString column_is_deleted(bool key = false) { Q_UNUSED(key); return "is_deleted"; }
   static QString column_last_synced(bool key = false) { Q_UNUSED(key); return "last_synced"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("User") : QString("user")); }

};

typedef std::shared_ptr<User> User_ptr;
typedef qx::QxCollection<quint64, User_ptr> list_of_User;
typedef std::shared_ptr<list_of_User> list_of_User_ptr;

QX_REGISTER_PRIMARY_KEY(User, quint64)
QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CLIENTMODELS(User, qx::trait::no_base_class_defined, 0, User)

#include "../include/RoomMembership.gen.h"
#include "../include/Message.gen.h"

#include "../custom/include/User.h"

#endif // _CLIENTMODELS_USER_H_
