/*
 * LightScheduler_Test.c
 *
 *  Created on: May 28, 2019
 *      Author: reser
 */

#include "LightScheduler_Test.h"

TimeService_Time StartTime;
TimeService_Time StopTime;
TimeService_Time EventTime[NumberOfEvents];
TimeService_Time ExpectedEventTime[NumberOfEvents];

LightController_DriverSpyEventType Expected;

LightController_DriverSpyEventType const Default =
{
   LIGHTCONTROLLER_ID_UNKNOWN,
   LIGHTCONTROLLER_STATE_ON,
   {
      TIMESERVICE_MONDAY,
      0
   }
};



void LightScheduler_Test_CheckEvent(LightController_DriverSpyEventType const * const ExpectedEvent, uint16 NumberGivenEvent)
{
   LightController_DriverSpyEventType Given;
   Given = LightController_DriverSpy_GetEvent(NumberGivenEvent);

   TEST_ASSERT_EQUAL(ExpectedEvent->Id, Given.Id);
   TEST_ASSERT_EQUAL(ExpectedEvent->State, Given.State);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Day, Given.Time.Day);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Minute, Given.Time.Minute);
}

static void SetTime(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Fake_SetDay(Day);
   TimeService_Fake_SetMinute(Minute);
}

void LightScheduler_Test_SetUp(void)
{
   int i;

   StartTime.Day = TIMESERVICE_MONDAY;
   StartTime.Minute = 0;
   StopTime = StartTime;

   for (i = 0; i < NumberOfEvents; i++)
   {
      EventTime[i] = StartTime;
      ExpectedEventTime[i] = StartTime;
   }

   TimeService_Fake_Init();
   LightController_Init(&LightController_Config);
   LightScheduler_Init(&LightSchedulerConfig);
   RandomMinute_Init(&RandomMinuteConfig);


   Expected = Default;
}

