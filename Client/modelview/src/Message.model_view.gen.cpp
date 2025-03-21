/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ClientModels_precompiled_header.model_view.gen.h"

#include "../include/Message.model_view.gen.h"
#include "../include/User.model_view.gen.h"
#include "../include/Room.model_view.gen.h"

#include <QxOrm_Impl.h>

namespace model_view {

Message_model::Message_model(QObject * parent /* = 0 */) : Message_model_base_class(parent) { ; }

Message_model::Message_model(qx::IxModel * other, QObject * parent) : Message_model_base_class(other, parent) { ; }

Message_model::~Message_model() { ; }

QObject * Message_model::user_id(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "user_id";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->rowCount())) { qAssert(false); return NULL; }
   Message_model_base_class::type_ptr ptr = this->getRowItemAt(row);
   if (! ptr) { qAssert(false); return NULL; }
   quint64 id = ptr->getid();
   Message::type_user_id value = ptr->getuser_id();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      Message tmp;
      tmp.setid(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getuser_id();
      ptr->setuser_id(value);
   }

   model_view::User_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "user_id", pChild); }
   return static_cast<QObject *>(pChild);
}

QObject * Message_model::room_id(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "room_id";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->rowCount())) { qAssert(false); return NULL; }
   Message_model_base_class::type_ptr ptr = this->getRowItemAt(row);
   if (! ptr) { qAssert(false); return NULL; }
   quint64 id = ptr->getid();
   Message::type_room_id value = ptr->getroom_id();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      Message tmp;
      tmp.setid(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getroom_id();
      ptr->setroom_id(value);
   }

   model_view::Room_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "room_id", pChild); }
   return static_cast<QObject *>(pChild);
}

void Message_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->rowCount())) { return; }
   Message_model_base_class::type_ptr ptr = this->getRowItemAt(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "user_id");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      Message::type_user_id value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setuser_id(value);
   }

   pNestedModel = this->getChild(row, "room_id");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      Message::type_room_id value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setroom_id(value);
   }
}

void Message_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->rowCount(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
