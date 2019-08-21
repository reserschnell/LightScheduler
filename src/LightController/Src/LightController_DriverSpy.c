/*
 * LightController_Spy.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "unity.h"
#include "LightController_DriverSpy.h"




#define LIGHTCONTROLLER_SPY_EVENTS 10


LightController_DriverSpyEventType Expected;

static const LightController_DriverSpyEventType Default =
{
   LIGHTCONTROLLER_ID_UNKNOWN,
   LIGHTCONTROLLER_STATE_ON,
   {
      TIMESERVICE_MONDAY,
      0
   }
};



typedef struct
{
   const LightController_DriverSpy_PipConstType * PipConst;
   const LightController_DriverSpy_PipCalibType * PipCalib;
} LightController_DriverSpy_SelfType;



typedef struct
{
   uint8 ModuleInitialized;
   uint16 EventCntr;
   sint32 LastCheckedEvent;
   LightController_DriverSpyEventType Given[LIGHTCONTROLLER_SPY_EVENTS];
} LightController_DriverSpy_SmType;



typedef struct
{
   LightController_DriverSpy_SmType Sm;
   LightController_DriverSpy_SelfType Self[LIGHTCONTROLLER_DRIVER_SPY_ID_MAX];
}LightController_DriverSpyType;



static LightController_DriverSpyType LightController_DriverSpy;

static void LightController_DriverSpy_On(uint8 DriverSpyId);

static void LightController_DriverSpy_Off(uint8 DriverSpyId);



void LightController_DriverSpy_Init(LightController_InterfaceType * const Interface,
      uint8 DriverSpyId,
      const LightController_DriverSpy_ConfigType * const Config)
{
   uint16 EventCntr;
   LightController_DriverSpy_SelfType * Self;



   // Initialize shared memory
   if (LightController_DriverSpy.Sm.ModuleInitialized != 0xAF)
   {
      // Initialize spy data
      LightController_DriverSpy.Sm.EventCntr = 0;
      LightController_DriverSpy.Sm.LastCheckedEvent = -1;

      Expected = Default;

      for (EventCntr = 0; EventCntr < LIGHTCONTROLLER_SPY_EVENTS; EventCntr++)
      {
         LightController_DriverSpy.Sm.Given[EventCntr] = Default;
      }
      LightController_DriverSpy.Sm.ModuleInitialized = 0xAF;
   }

   // Set interface
   Interface->DriverOff = LightController_DriverSpy_Off;
   Interface->DriverOn = LightController_DriverSpy_On;

   // Initialize self memory
   Self = &(LightController_DriverSpy.Self[DriverSpyId]);
   Self->PipConst = &(Config->PipConst[DriverSpyId]);
   Self->PipCalib = &(Config->PipCalib[DriverSpyId]);
}

void LightController_DriverSpy_DeInit(void)
{
   LightController_DriverSpy.Sm.ModuleInitialized = 0;
}


static inline void LightController_Spy_lSetEvent(
      LightController_IdType LightControllerId,
      LightController_StateType State)
{
   LightController_DriverSpy_SmType * const Sm = &(LightController_DriverSpy.Sm);
   LightController_DriverSpyEventType * const Given =
         &(LightController_DriverSpy.Sm.Given[Sm->EventCntr]);
   TimeService_Time Time;

   TimeService_GetTime(&Time);

   Given->LightControllerId = LightControllerId;
   Given->State = State;
   Given->Time = Time;
   Sm->EventCntr++;
   if (Sm->EventCntr >= LIGHTCONTROLLER_SPY_EVENTS)
   {
      Sm->EventCntr = 0;
   }
}

static void LightController_DriverSpy_On(uint8 DriverSpyId)
{
   LightController_IdType LightControllerId =
         LightController_DriverSpy.Self[DriverSpyId].PipConst->LightControllerId;

   LightController_Spy_lSetEvent(LightControllerId, LIGHTCONTROLLER_STATE_ON);
}

static void LightController_DriverSpy_Off(uint8 DriverSpyId)
{
   LightController_IdType LightControllerId =
         LightController_DriverSpy.Self[DriverSpyId].PipConst->LightControllerId;

   LightController_Spy_lSetEvent(LightControllerId, LIGHTCONTROLLER_STATE_OFF);
}


static LightController_DriverSpyEventType LightController_DriverSpy_GetEvent(uint16 EventNumber)
{
   return (LightController_DriverSpy.Sm.Given[EventNumber]);
}


void LightController_DriverSpy_CheckEvent(const LightController_DriverSpyEventType * const ExpectedEvent, const uint16 NumberGivenEvent)
{
   LightController_DriverSpyEventType Given;
   Given = LightController_DriverSpy_GetEvent(NumberGivenEvent);

   if (LightController_DriverSpy.Sm.LastCheckedEvent < NumberGivenEvent)
   {
      LightController_DriverSpy.Sm.LastCheckedEvent = NumberGivenEvent;
   }

   TEST_ASSERT_EQUAL(ExpectedEvent->LightControllerId, Given.LightControllerId);
   TEST_ASSERT_EQUAL(ExpectedEvent->State, Given.State);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Day, Given.Time.Day);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Minute, Given.Time.Minute);
}

void LightController_DriverSpy_CheckDefault(void)
{
   uint16 NumberEvent = LightController_DriverSpy.Sm.LastCheckedEvent + 1;

   LightController_DriverSpy_CheckEvent(&Default, NumberEvent);
}



LightController_DriverSpyEventType LightController_DriverSpy_GetDefault(void)
{
   return Default;
}

