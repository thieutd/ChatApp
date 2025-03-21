/************************************************************************************************
** File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CLIENTMODELS_ROOMTYPE_H_
#define _CLIENTMODELS_ROOMTYPE_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/ClientModels_precompiled_header.gen.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

class CLIENTMODELS_EXPORT RoomType : public QObject
{
    Q_OBJECT

public:

   enum enum_RoomType
   {
      direct = 0,
      group = 1
   };
   Q_ENUM(enum_RoomType)

   private:

   RoomType();
   virtual ~RoomType();

};

#include "../custom/include/RoomType.h"

#endif // _CLIENTMODELS_ROOMTYPE_H_
