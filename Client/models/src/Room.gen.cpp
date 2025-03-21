/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ClientModels_precompiled_header.gen.h"

#include "../include/Room.gen.h"
#include "../include/RoomMembership.gen.h"
#include "../include/Message.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CLIENTMODELS(Room, Room)

namespace qx {

template <>
void register_class(QxClass<Room> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("room");
   t.setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.id(& Room::m_id, "id", 0);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.data(& Room::m_name, "name", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_type, "type", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_description, "description", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_avatar_url, "avatar_url", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_created_at, "created_at", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_is_deleted, "is_deleted", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_last_message_id, "last_message_id", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Room::m_last_synced, "last_synced", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pRelation = t.relationOneToMany(& Room::m_list_of_room_membership, "list_of_room_membership", "room_id", 0);
   pRelation = t.relationOneToMany(& Room::m_list_of_message, "list_of_message", "room_id", 0);

   qx::QxValidatorX<Room> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

QX_PERSISTABLE_CPP(Room)

Room::Room() : m_id(0), m_is_deleted(false), m_last_message_id(0) { ; }

Room::Room(const quint64 & id) : m_id(id), m_is_deleted(false), m_last_message_id(0) { ; }

Room::~Room() { ; }

quint64 Room::getid() const { return m_id; }

QString Room::getname() const { return m_name; }

RoomType::enum_RoomType Room::gettype() const { return m_type; }

QString Room::getdescription() const { return m_description; }

QString Room::getavatar_url() const { return m_avatar_url; }

QDateTime Room::getcreated_at() const { return m_created_at; }

bool Room::getis_deleted() const { return m_is_deleted; }

qint64 Room::getlast_message_id() const { return m_last_message_id; }

QDateTime Room::getlast_synced() const { return m_last_synced; }

Room::type_list_of_room_membership Room::getlist_of_room_membership() const { return m_list_of_room_membership; }

Room::type_list_of_room_membership & Room::list_of_room_membership() { return m_list_of_room_membership; }

const Room::type_list_of_room_membership & Room::list_of_room_membership() const { return m_list_of_room_membership; }

Room::type_list_of_message Room::getlist_of_message() const { return m_list_of_message; }

Room::type_list_of_message & Room::list_of_message() { return m_list_of_message; }

const Room::type_list_of_message & Room::list_of_message() const { return m_list_of_message; }

void Room::setid(const quint64 & val) { m_id = val; }

void Room::setname(const QString & val) { m_name = val; }

void Room::settype(const RoomType::enum_RoomType & val) { m_type = val; }

void Room::setdescription(const QString & val) { m_description = val; }

void Room::setavatar_url(const QString & val) { m_avatar_url = val; }

void Room::setcreated_at(const QDateTime & val) { m_created_at = val; }

void Room::setis_deleted(const bool & val) { m_is_deleted = val; }

void Room::setlast_message_id(const qint64 & val) { m_last_message_id = val; }

void Room::setlast_synced(const QDateTime & val) { m_last_synced = val; }

void Room::setlist_of_room_membership(const Room::type_list_of_room_membership & val) { m_list_of_room_membership = val; }

void Room::setlist_of_message(const Room::type_list_of_message & val) { m_list_of_message = val; }

Room::type_list_of_room_membership Room::getlist_of_room_membership(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_room_membership(); }
   QString sRelation = "{id} | list_of_room_membership";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Room tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_room_membership = tmp.m_list_of_room_membership; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_room_membership;
}

Room::type_list_of_room_membership & Room::list_of_room_membership(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_room_membership(); }
   QString sRelation = "{id} | list_of_room_membership";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Room tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_room_membership = tmp.m_list_of_room_membership; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_room_membership;
}

Room::type_list_of_message Room::getlist_of_message(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_message(); }
   QString sRelation = "{id} | list_of_message";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Room tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_message = tmp.m_list_of_message; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_message;
}

Room::type_list_of_message & Room::list_of_message(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_message(); }
   QString sRelation = "{id} | list_of_message";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Room tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_message = tmp.m_list_of_message; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_message;
}

