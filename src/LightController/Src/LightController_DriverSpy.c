/*
 * LightController_Spy.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "LightController_DriverSpy.h"




#define LIGHTCONTROLLER_SPY_EVENTS 10



typedef struct
{
   LightController_DriverSpyEventType Given;
} LightController_SpyDataType;


typedef struct
{
   uint16 EventCntr;
} LightController_SpyMDataType;



typedef struct
{
   LightController_SpyDataType Data[LIGHTCONTROLLER_SPY_EVENTS];
   LightController_SpyMDataType MData;
}LightController_SpyType;



static LightController_SpyType LightController_Spy;

static void LightController_DriverSpy_On(uint8 DriverId);

static void LightController_DriverSpy_Off(uint8 DriverId);



void LightController_DriverSpy_Init(LightController_InterfaceType * const Interface,
      LightController_DriverSpyConfigType const * const Config)
{
   uint16 EventCntr;
   LightController_SpyDataType * DataPtr;

   // Initialize spy data
   LightController_Spy.MData.EventCntr = 0;

   for (EventCntr = 0; EventCntr < LIGHTCONTROLLER_SPY_EVENTS; EventCntr++)
   {
      DataPtr = &(LightController_Spy.Data[EventCntr]);
      DataPtr->Given.Id = LIGHTCONTROLLER_ID_UNKNOWN;
      DataPtr->Given.State = LIGHTCONTROLLER_STATE_ON;
      DataPtr->Given.Time.Day = TIMESERVICE_MONDAY;
      DataPtr->Given.Time.Minute = 0;
   }

   // Set interface
   Interface->DriverOff = LightController_DriverSpy_Off;
   Interface->DriverOn = LightController_DriverSpy_On;
}

static inline void LightController_Spy_lSetEvent(
      LightController_IdType Id,
      LightController_StateType State)
{
   LightController_SpyMDataType* const MDataPtr = &(LightController_Spy.MData);
   LightController_SpyDataType* const DataPtr =
         &(LightController_Spy.Data[MDataPtr->EventCntr]);
   TimeService_Time Time;

   TimeService_GetTime(&Time);

   DataPtr->Given.Id = Id;
   DataPtr->Given.State = State;
   DataPtr->Given.Time = Time;
   MDataPtr->EventCntr++;
   if (MDataPtr->EventCntr >= LIGHTCONTROLLER_SPY_EVENTS)
   {
      MDataPtr->EventCntr = 0;
   }
}

static void LightController_DriverSpy_On(uint8 Id)
{

   LightController_Spy_lSetEvent(Id, LIGHTCONTROLLER_STATE_ON);

}

static void LightController_DriverSpy_Off(uint8 Id)
{

   LightController_Spy_lSetEvent(Id, LIGHTCONTROLLER_STATE_OFF);
}


LightController_DriverSpyEventType LightController_DriverSpy_GetEvent(uint16 EventNumber)
{
   return (LightController_Spy.Data[EventNumber].Given);
}



