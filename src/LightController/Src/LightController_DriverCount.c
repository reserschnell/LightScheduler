/*
 * LightController_Spy.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "LightController_DriverCount.h"




typedef struct
{
   uint16 EventCntr;
} LightController_CountSmType;



typedef struct
{
   LightController_CountSmType Sm;
}LightController_CountType;



static LightController_CountType LightController_Count;

static void LightController_DriverCount_On(uint8 DriverId);

static void LightController_DriverCount_Off(uint8 DriverId);



void LightController_DriverCount_Init(LightController_InterfaceType * const Interface,
      LightController_DriverCountConfigType const * const Config)
{

   // Initialize spy data
   LightController_Count.Sm.EventCntr = 0;

   // Set interface
   Interface->DriverOff = LightController_DriverCount_Off;
   Interface->DriverOn = LightController_DriverCount_On;
}

static inline void LightController_Count_lSetEvent(
      LightController_IdType Id,
      LightController_StateType State)
{
   LightController_CountSmType* const MDataPtr = &(LightController_Count.Sm);

   MDataPtr->EventCntr++;

}

static void LightController_DriverCount_On(uint8 Id)
{

   LightController_Count_lSetEvent(Id, LIGHTCONTROLLER_STATE_ON);

}

static void LightController_DriverCount_Off(uint8 Id)
{

   LightController_Count_lSetEvent(Id, LIGHTCONTROLLER_STATE_OFF);
}


uint16 LightController_DriverCount_GetEventCntr(void)
{
   return (LightController_Count.Sm.EventCntr);
}



