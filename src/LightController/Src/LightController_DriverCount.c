/*
 * LightController_Spy.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "LightController_DriverCount.h"



typedef struct
{
   uint8 ModuleInitialized;
   uint16 EventCntr;
} LightController_DriverCount_SmType;



typedef struct
{
   LightController_DriverCount_SmType Sm;
}LightController_DriverCount_Type;




static LightController_DriverCount_Type LightController_DriverCount;

static void LightController_DriverCount_On(uint8 DriverCountId);

static void LightController_DriverCount_Off(uint8 DriverCountId);



void LightController_DriverCount_Init(LightController_InterfaceType * const Interface,
      uint8 DriverCountId,
      const void * const Config)
{

   // Set shared memory
   if (LightController_DriverCount.Sm.ModuleInitialized != 0xAF)
   {
      LightController_DriverCount.Sm.EventCntr = 0;
      LightController_DriverCount.Sm.ModuleInitialized = 0xAF;
   }

   // Set interface
   Interface->DriverOff = LightController_DriverCount_Off;
   Interface->DriverOn = LightController_DriverCount_On;
}

void LightController_DriverCount_DeInit(void)
{
   LightController_DriverCount.Sm.ModuleInitialized = 0;
}

static inline void LightController_DriverCount_lSetEvent(void)
{
   LightController_DriverCount.Sm.EventCntr++;

}

static void LightController_DriverCount_On(uint8 DriverCountId)
{

   LightController_DriverCount_lSetEvent();

}

static void LightController_DriverCount_Off(uint8 DriverCountId)
{

   LightController_DriverCount_lSetEvent();
}


uint16 LightController_DriverCount_GetEventCntr(void)
{
   return (LightController_DriverCount.Sm.EventCntr);
}



