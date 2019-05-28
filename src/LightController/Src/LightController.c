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
} LightController_DataType;


typedef struct
{
   LightController_DataType Data[LIGHTCONTROLLER_ID_MAX];
}LightController_Type;

LightController_Type LightController;


void LightController_Init(LightController_MConfigType const * const MConfig)
{

   uint8 i;

   for (i = 0; i < LIGHTCONTROLLER_ID_MAX; i++)
   {
      LightController_SetDriver((LightController_IdType)i,
            &(MConfig->Config[i] ));
   }

}

void LightController_SetDriver(LightController_IdType Id,
      LightController_ConfigType const * const Config)
{
   LightController_InterfaceType * Interface;


   Interface = &(LightController.Data[Id].Interface);

   Config->DriverInit(Interface, Config);
}

void LightController_On(LightController_IdType Id)
{
   LightController_InterfaceType * Interface;

   Interface = &(LightController.Data[Id].Interface);

   Interface->DriverOn(Id);
}

void LightController_Off(LightController_IdType Id)
{
   LightController_InterfaceType * Interface;

   Interface = &(LightController.Data[Id].Interface);

   Interface->DriverOff(Id);
}
