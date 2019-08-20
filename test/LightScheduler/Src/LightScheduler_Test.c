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
#include "LightController_DriverSpy.h"




void LightScheduler_Test_SetUp(void)
{
   LightController_DriverSpyEventType Default;


   TimeService_Os_GetTime_StubWithCallback(TimeService_Os_GetTime_CALLBACK);

   Default = LightController_DriverSpy_GetDefault();
   TimeService_Os_Mock_SetTime(Default.Time.Day, Default.Time.Minute);

   LightController_Init(&LightController_Config);
   LightScheduler_Init(&LightSchedulerConfig);
   RandomMinute_Init(&RandomMinute_Config);

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

