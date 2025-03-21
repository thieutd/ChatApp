/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ClientModels_precompiled_header.model_view.gen.h"

#include "../include/User.model_view.gen.h"
#include "../include/RoomMembership.model_view.gen.h"
#include "../include/Message.model_view.gen.h"

#include <QxOrm_Impl.h>

namespace model_view {

User_model::User_model(QObject * parent /* = 0 */) : User_model_base_class(parent) { ; }

User_model::User_model(qx::IxModel * other, QObject * parent) : User_model_base_class(other, parent) { ; }

User_model::~User_model() { ; }

QObject * User_model::list_of_room_membership(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_of_room_membership";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->rowCount())) { qAssert(false); return NULL; }
   User_model_base_class::type_ptr ptr = this->getRowItemAt(row);
   if (! ptr) { qAssert(false); return NULL; }
   quint64 id = ptr->getid();
   User::type_list_of_room_membership value = ptr->getlist_of_room_membership();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      User tmp;
      tmp.setid(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_room_membership();
      ptr->setlist_of_room_membership(value);
   }

   model_view::RoomMembership_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_of_room_membership", pChild); }
   return static_cast<QObject *>(pChild);
}

QObject * User_model::list_of_message(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_of_message";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->rowCount())) { qAssert(false); return NULL; }
   User_model_base_class::type_ptr ptr = this->getRowItemAt(row);
   if (! ptr) { qAssert(false); return NULL; }
   quint64 id = ptr->getid();
   User::type_list_of_message value = ptr->getlist_of_message();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      User tmp;
      tmp.setid(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_message();
      ptr->setlist_of_message(value);
   }

   model_view::Message_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_of_message", pChild); }
   return static_cast<QObject *>(pChild);
}

void User_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->rowCount())) { return; }
   User_model_base_class::type_ptr ptr = this->getRowItemAt(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "list_of_room_membership");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      User::type_list_of_room_membership value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_room_membership(value);
   }

   pNestedModel = this->getChild(row, "list_of_message");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      User::type_list_of_message value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_message(value);
   }
}

void User_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->rowCount(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
