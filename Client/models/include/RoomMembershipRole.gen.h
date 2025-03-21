/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_ROOMMEMBERSHIPROLE_H_
#define _CLIENTMODELS_ROOMMEMBERSHIPROLE_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/ClientModels_precompiled_header.gen.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

class CLIENTMODELS_EXPORT RoomMembershipRole : public QObject
{

   Q_OBJECT
   Q_ENUMS(enum_RoomMembershipRole)

public:

   enum enum_RoomMembershipRole
   {
      admin = 0,
      member = 1
   };

private:

   RoomMembershipRole();
   virtual ~RoomMembershipRole();

};

#include "../custom/include/RoomMembershipRole.h"

#endif // _CLIENTMODELS_ROOMMEMBERSHIPROLE_H_
