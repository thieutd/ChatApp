/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_USERROLE_H_
#define _CLIENTMODELS_USERROLE_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/ClientModels_precompiled_header.gen.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

class CLIENTMODELS_EXPORT UserRole : public QObject
{
    Q_OBJECT

public:

   enum enum_UserRole
   {
      admin = 0,
      user = 1
   };
   Q_ENUM(enum_UserRole)

   private:

   UserRole();
   virtual ~UserRole();

};

#include "../custom/include/UserRole.h"

#endif // _CLIENTMODELS_USERROLE_H_
