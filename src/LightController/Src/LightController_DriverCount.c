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
} LightController_CountMDataType;



typedef struct
{
   LightController_CountMDataType MData;
}LightController_CountType;



static LightController_CountType LightController_Count;

static void LightController_DriverCount_On(uint8 DriverId);

static void LightController_DriverCount_Off(uint8 DriverId);



void LightController_DriverCount_Init(LightController_InterfaceType * const Interface,
      LightController_DriverCountConfigType const * const Config)
{
   uint16 EventCntr;

   // Initialize spy data
   LightController_Count.MData.EventCntr = 0;

   // Set interface
   Interface->DriverOff = LightController_DriverCount_Off;
   Interface->DriverOn = LightController_DriverCount_On;
}

static inline void LightController_Count_lSetEvent(
      LightController_IdType Id,
      LightController_StateType State)
{
   LightController_CountMDataType* const MDataPtr = &(LightController_Count.MData);

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
   return (LightController_Count.MData.EventCntr);
}



