/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_ROOMMEMBERSHIP_H_
#define _CLIENTMODELS_ROOMMEMBERSHIP_H_

#include "../include/RoomMembershipRole.gen.h"

class User;
class Room;

class CLIENTMODELS_EXPORT RoomMembership : public qx::IxPersistable
{

   QX_REGISTER_FRIEND_CLASS(RoomMembership)

   QX_PERSISTABLE_HPP(RoomMembership)

public:

   typedef std::shared_ptr<User> type_user_id;
   typedef std::shared_ptr<Room> type_room_id;

protected:

   QPair<quint64,quint64> m_user_id_room_id;
   RoomMembershipRole::enum_RoomMembershipRole m_role;
   QDateTime m_created_at;
   bool m_is_deleted;
   QDateTime m_last_synced;
   type_user_id m_user_id;
   type_room_id m_room_id;

public:

   RoomMembership();
   RoomMembership(const QPair<quint64,quint64> & id);
   virtual ~RoomMembership();

   QPair<quint64,quint64> getuser_id_room_id() const;
   RoomMembershipRole::enum_RoomMembershipRole getrole() const;
   QDateTime getcreated_at() const;
   bool getis_deleted() const;
   QDateTime getlast_synced() const;
   type_user_id getuser_id() const;
   type_room_id getroom_id() const;

   void setuser_id_room_id(const QPair<quint64,quint64> & val);
   void setrole(const RoomMembershipRole::enum_RoomMembershipRole & val);
   void setcreated_at(const QDateTime & val);
   void setis_deleted(const bool & val);
   void setlast_synced(const QDateTime & val);
   void setuser_id(const type_user_id & val);
   void setroom_id(const type_room_id & val);

   type_user_id getuser_id(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_room_id getroom_id(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_user_id(bool key = false) { Q_UNUSED(key); return "user_id"; }
   static QString relation_room_id(bool key = false) { Q_UNUSED(key); return "room_id"; }

public:

   static QString column_user_id_room_id(bool key = false) { return (key ? QString("user_id_room_id") : QString("user_id|room_id")); }
   static QString column_role(bool key = false) { Q_UNUSED(key); return "role"; }
   static QString column_created_at(bool key = false) { Q_UNUSED(key); return "created_at"; }
   static QString column_is_deleted(bool key = false) { Q_UNUSED(key); return "is_deleted"; }
   static QString column_last_synced(bool key = false) { Q_UNUSED(key); return "last_synced"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("RoomMembership") : QString("room_membership")); }

};

typedef std::shared_ptr<RoomMembership> RoomMembership_ptr;
typedef qx::QxCollection<QPair<quint64,quint64>, RoomMembership_ptr> list_of_RoomMembership;
typedef std::shared_ptr<list_of_RoomMembership> list_of_RoomMembership_ptr;

typedef QPair<quint64,quint64> type_RoomMembership_primary_key;
QX_REGISTER_PRIMARY_KEY(RoomMembership, type_RoomMembership_primary_key)
QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CLIENTMODELS(RoomMembership, qx::trait::no_base_class_defined, 0, RoomMembership)

#include "../include/User.gen.h"
#include "../include/Room.gen.h"

#include "../custom/include/RoomMembership.h"

#endif // _CLIENTMODELS_ROOMMEMBERSHIP_H_
