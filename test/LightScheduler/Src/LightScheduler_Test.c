/*
 * LightScheduler_Test.c
 *
 *  Created on: May 28, 2019
 *      Author: reser
 */

#include "LightScheduler_Test.h"

#include "unity.h"
#include "TimeService_Os_Mock.h"
#include "mock_TimeService_Os.h"
#include "LightScheduler_PBcfg.h"
#include "LightController_PBcfg.h"
#include "RandomMinute_PBcfg.h"


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
   sint32 LastCheckedEvent;
}LightScheduler_TestType;

static LightScheduler_TestType LightScheduler_Test;



void LightScheduler_Test_SetUp(void)
{

   TimeService_Os_GetTime_StubWithCallback(TimeService_Os_GetTime_CALLBACK);
   TimeService_Os_Mock_SetTime(Default.Time.Day, Default.Time.Minute);

   LightController_Init(&LightController_Config);
   LightScheduler_Init(&LightSchedulerConfig);
   RandomMinute_Init(&RandomMinuteConfig);

   LightScheduler_Test.LastCheckedEvent = -1;
   Expected = Default;

}


void LightScheduler_Test_RunUntil(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Time StopTime;

   StopTime.Day = Day;
   StopTime.Minute = Minute;

   while ( !TimeService_IsNowEqualTo(&StopTime))
   {
      LightScheduler_MainFunction();
      TimeService_Os_Mock_IncrementTime();
   }
}


void LightScheduler_Test_CheckEvent(LightController_DriverSpyEventType const * const ExpectedEvent, uint16 NumberGivenEvent)
{
   LightController_DriverSpyEventType Given;
   Given = LightController_DriverSpy_GetEvent(NumberGivenEvent);

   if (LightScheduler_Test.LastCheckedEvent < NumberGivenEvent)
   {
      LightScheduler_Test.LastCheckedEvent = NumberGivenEvent;
   }

   TEST_ASSERT_EQUAL(ExpectedEvent->Id, Given.Id);
   TEST_ASSERT_EQUAL(ExpectedEvent->State, Given.State);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Day, Given.Time.Day);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Minute, Given.Time.Minute);
}

void LightScheduler_Test_CheckDefault(void)
{
   uint16 NumberEvent = LightScheduler_Test.LastCheckedEvent + 1;

   LightScheduler_Test_CheckEvent(&Default, NumberEvent);
}

