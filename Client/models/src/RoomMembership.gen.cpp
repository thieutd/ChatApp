/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ClientModels_precompiled_header.gen.h"

#include "../include/RoomMembership.gen.h"
#include "../include/User.gen.h"
#include "../include/Room.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CLIENTMODELS(RoomMembership, RoomMembership)

namespace qx {

template <>
void register_class(QxClass<RoomMembership> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("room_membership");
   t.setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.id(& RoomMembership::m_user_id_room_id, "user_id_room_id", 0);
   pData->setName("user_id|room_id");
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.data(& RoomMembership::m_role, "role", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& RoomMembership::m_created_at, "created_at", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& RoomMembership::m_is_deleted, "is_deleted", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& RoomMembership::m_last_synced, "last_synced", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pRelation = t.relationManyToOne(& RoomMembership::m_user_id, "user_id", 0);
   pRelation->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pRelation = t.relationManyToOne(& RoomMembership::m_room_id, "room_id", 0);
   pRelation->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   qx::QxValidatorX<RoomMembership> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

QX_PERSISTABLE_CPP(RoomMembership)

RoomMembership::RoomMembership() : m_is_deleted(false) { ; }

RoomMembership::RoomMembership(const QPair<quint64,quint64> & id) : m_user_id_room_id(id), m_is_deleted(false) { ; }

RoomMembership::~RoomMembership() { ; }

QPair<quint64,quint64> RoomMembership::getuser_id_room_id() const { return m_user_id_room_id; }

RoomMembershipRole::enum_RoomMembershipRole RoomMembership::getrole() const { return m_role; }

QDateTime RoomMembership::getcreated_at() const { return m_created_at; }

bool RoomMembership::getis_deleted() const { return m_is_deleted; }

QDateTime RoomMembership::getlast_synced() const { return m_last_synced; }

RoomMembership::type_user_id RoomMembership::getuser_id() const { return m_user_id; }

RoomMembership::type_room_id RoomMembership::getroom_id() const { return m_room_id; }

void RoomMembership::setuser_id_room_id(const QPair<quint64,quint64> & val) { m_user_id_room_id = val; }

void RoomMembership::setrole(const RoomMembershipRole::enum_RoomMembershipRole & val) { m_role = val; }

void RoomMembership::setcreated_at(const QDateTime & val) { m_created_at = val; }

void RoomMembership::setis_deleted(const bool & val) { m_is_deleted = val; }

void RoomMembership::setlast_synced(const QDateTime & val) { m_last_synced = val; }

void RoomMembership::setuser_id(const RoomMembership::type_user_id & val) { m_user_id = val; }

void RoomMembership::setroom_id(const RoomMembership::type_room_id & val) { m_room_id = val; }

RoomMembership::type_user_id RoomMembership::getuser_id(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getuser_id(); }
   QString sRelation = "{user_id_room_id} | user_id";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   RoomMembership tmp;
   tmp.m_user_id_room_id = this->m_user_id_room_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_user_id = tmp.m_user_id; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_user_id;
}

RoomMembership::type_room_id RoomMembership::getroom_id(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getroom_id(); }
   QString sRelation = "{user_id_room_id} | room_id";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   RoomMembership tmp;
   tmp.m_user_id_room_id = this->m_user_id_room_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_room_id = tmp.m_room_id; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_room_id;
}

