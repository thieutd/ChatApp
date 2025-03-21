/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ClientModels_precompiled_header.gen.h"

#include "../include/User.gen.h"
#include "../include/RoomMembership.gen.h"
#include "../include/Message.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CLIENTMODELS(User, User)

namespace qx {

template <>
void register_class(QxClass<User> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("user");
   t.setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.id(& User::m_id, "id", 0);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData->setAutoIncrement(false);

   pData = t.data(& User::m_username, "username", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& User::m_role, "role", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& User::m_avatar_url, "avatar_url", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& User::m_created_at, "created_at", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& User::m_is_deleted, "is_deleted", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& User::m_last_synced, "last_synced", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pRelation = t.relationOneToMany(& User::m_list_of_room_membership, "list_of_room_membership", "user_id", 0);
   pRelation = t.relationOneToMany(& User::m_list_of_message, "list_of_message", "user_id", 0);

   qx::QxValidatorX<User> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

QX_PERSISTABLE_CPP(User)

User::User() : m_id(0), m_is_deleted(false) { ; }

User::User(const quint64 & id) : m_id(id), m_is_deleted(false) { ; }

User::~User() { ; }

quint64 User::getid() const { return m_id; }

QString User::getusername() const { return m_username; }

UserRole::enum_UserRole User::getrole() const { return m_role; }

QString User::getavatar_url() const { return m_avatar_url; }

QDateTime User::getcreated_at() const { return m_created_at; }

bool User::getis_deleted() const { return m_is_deleted; }

QDateTime User::getlast_synced() const { return m_last_synced; }

User::type_list_of_room_membership User::getlist_of_room_membership() const { return m_list_of_room_membership; }

User::type_list_of_room_membership & User::list_of_room_membership() { return m_list_of_room_membership; }

const User::type_list_of_room_membership & User::list_of_room_membership() const { return m_list_of_room_membership; }

User::type_list_of_message User::getlist_of_message() const { return m_list_of_message; }

User::type_list_of_message & User::list_of_message() { return m_list_of_message; }

const User::type_list_of_message & User::list_of_message() const { return m_list_of_message; }

void User::setid(const quint64 & val) { m_id = val; }

void User::setusername(const QString & val) { m_username = val; }

void User::setrole(const UserRole::enum_UserRole & val) { m_role = val; }

void User::setavatar_url(const QString & val) { m_avatar_url = val; }

void User::setcreated_at(const QDateTime & val) { m_created_at = val; }

void User::setis_deleted(const bool & val) { m_is_deleted = val; }

void User::setlast_synced(const QDateTime & val) { m_last_synced = val; }

void User::setlist_of_room_membership(const User::type_list_of_room_membership & val) { m_list_of_room_membership = val; }

void User::setlist_of_message(const User::type_list_of_message & val) { m_list_of_message = val; }

User::type_list_of_room_membership User::getlist_of_room_membership(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_room_membership(); }
   QString sRelation = "{id} | list_of_room_membership";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   User tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_room_membership = tmp.m_list_of_room_membership; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_room_membership;
}

User::type_list_of_room_membership & User::list_of_room_membership(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_room_membership(); }
   QString sRelation = "{id} | list_of_room_membership";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   User tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_room_membership = tmp.m_list_of_room_membership; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_room_membership;
}

User::type_list_of_message User::getlist_of_message(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_message(); }
   QString sRelation = "{id} | list_of_message";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   User tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_message = tmp.m_list_of_message; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_message;
}

User::type_list_of_message & User::list_of_message(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_message(); }
   QString sRelation = "{id} | list_of_message";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   User tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_message = tmp.m_list_of_message; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_message;
}

