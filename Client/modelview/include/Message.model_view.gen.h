/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_MESSAGE_MODEL_VIEW_H_
#define _CLIENTMODELS_MESSAGE_MODEL_VIEW_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/ClientModels_precompiled_header.model_view.gen.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include "../../models/include/Message.gen.h"

namespace model_view {

typedef qx::QxModel<Message> Message_model_base_class;

class CLIENTMODELS_MODEL_VIEW_EXPORT Message_model : public Message_model_base_class
{

   Q_OBJECT

public:

   Message_model(QObject * parent = 0);
   Message_model(qx::IxModel * other, QObject * parent);
   virtual ~Message_model();

   Q_INVOKABLE QObject * user_id(int row, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString());
   Q_INVOKABLE QObject * room_id(int row, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString());

   /* List of properties exposed by the model (7) :
      - id
      - content
      - created_at
      - is_deleted
      - is_sent
      - pending_id
      - last_synced
   */

protected:

   virtual void syncNestedModel(int row, const QStringList & relation);
   virtual void syncAllNestedModel(const QStringList & relation);

};

} // namespace model_view

#endif // _CLIENTMODELS_MESSAGE_MODEL_VIEW_H_
