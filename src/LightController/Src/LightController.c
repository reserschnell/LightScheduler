/*
 * LightController.c
 *
 *  Created on: Jan 30, 2019
 *      Author: reser
 */

#include "LightController_Driver.h"
#include "LightController.h"

typedef struct
{
   LightController_InterfaceType Interface;
} LightController_PimType;


typedef struct
{
   const LightController_PipConstType * PipConst;
   LightController_PimType Sm;
} LightController_SelfType;


typedef struct
{
   LightController_SelfType Self[LIGHTCONTROLLER_ID_MAX];
}LightController_Type;

static LightController_Type LightController;


void LightController_Init(const LightController_ConfigType * const Config)
{

   uint8 Id;
   LightController_SelfType * Self;

   for (Id = 0; Id < LIGHTCONTROLLER_ID_MAX; Id++)
   {
      Self = &(LightController.Self[Id]);
      Self->PipConst = &(Config->PipConst[Id]);
      LightController_SetDriver((LightController_IdType)Id,
            &(Config->PipConst[Id]));
   }

}

void LightController_SetDriver(LightController_IdType Id,
      const LightController_PipConstType * const PipConst)
{
   LightController_InterfaceType * Interface;


   Interface = &(LightController.Self[Id].Sm.Interface);

   PipConst->DriverInit(Interface, PipConst->DriverId, PipConst->DriverConfig);
}

void LightController_On(LightController_IdType Id)
{
   LightController_InterfaceType * Interface;
   uint8 DriverId;
   LightController_SelfType Self;

   Self = LightController.Self[Id];

   Interface = &(Self.Sm.Interface);
   DriverId = Self.PipConst->DriverId;

   Interface->DriverOn(DriverId);
}

void LightController_Off(LightController_IdType Id)
{
   LightController_InterfaceType * Interface;
   uint8 DriverId;
   LightController_SelfType Self;

   Self = LightController.Self[Id];

   Interface = &(Self.Sm.Interface);
   DriverId = Self.PipConst->DriverId;

   Interface->DriverOff(DriverId);
}
