/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ClientModels_precompiled_header.gen.h"

#include "../include/Message.gen.h"
#include "../include/User.gen.h"
#include "../include/Room.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CLIENTMODELS(Message, Message)

namespace qx {

template <>
void register_class(QxClass<Message> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("message");
   t.setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.id(& Message::m_id, "id", 0);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pData = t.data(& Message::m_content, "content", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Message::m_created_at, "created_at", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Message::m_is_deleted, "is_deleted", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Message::m_is_sent, "is_sent", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData = t.data(& Message::m_pending_id, "pending_id", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pData->setIsIndex(true);
   pData = t.data(& Message::m_last_synced, "last_synced", 0, true, true);
   pData->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   pRelation = t.relationManyToOne(& Message::m_user_id, "user_id", 0);
   pRelation->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");
   pRelation = t.relationManyToOne(& Message::m_room_id, "room_id", 0);
   pRelation->setPropertyBag("QX_EE_GENERATED_BY_SQLITE_IMPORT_PLUGIN", "1");

   qx::QxValidatorX<Message> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

QX_PERSISTABLE_CPP(Message)

Message::Message() : m_id(0), m_is_deleted(false), m_is_sent(false), m_pending_id(0) { ; }

Message::Message(const quint64 & id) : m_id(id), m_is_deleted(false), m_is_sent(false), m_pending_id(0) { ; }

Message::~Message() { ; }

quint64 Message::getid() const { return m_id; }

QString Message::getcontent() const { return m_content; }

QDateTime Message::getcreated_at() const { return m_created_at; }

bool Message::getis_deleted() const { return m_is_deleted; }

bool Message::getis_sent() const { return m_is_sent; }

quint64 Message::getpending_id() const { return m_pending_id; }

QDateTime Message::getlast_synced() const { return m_last_synced; }

Message::type_user_id Message::getuser_id() const { return m_user_id; }

Message::type_room_id Message::getroom_id() const { return m_room_id; }

void Message::setid(const quint64 & val) { m_id = val; }

void Message::setcontent(const QString & val) { m_content = val; }

void Message::setcreated_at(const QDateTime & val) { m_created_at = val; }

void Message::setis_deleted(const bool & val) { m_is_deleted = val; }

void Message::setis_sent(const bool & val) { m_is_sent = val; }

void Message::setpending_id(const quint64 & val) { m_pending_id = val; }

void Message::setlast_synced(const QDateTime & val) { m_last_synced = val; }

void Message::setuser_id(const Message::type_user_id & val) { m_user_id = val; }

void Message::setroom_id(const Message::type_room_id & val) { m_room_id = val; }

Message::type_user_id Message::getuser_id(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getuser_id(); }
   QString sRelation = "{id} | user_id";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Message tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_user_id = tmp.m_user_id; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_user_id;
}

Message::type_room_id Message::getroom_id(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getroom_id(); }
   QString sRelation = "{id} | room_id";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Message tmp;
   tmp.m_id = this->m_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_room_id = tmp.m_room_id; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_room_id;
}

