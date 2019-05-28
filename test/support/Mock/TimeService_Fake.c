/*
 * TimeService_Fake.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#include "Std_Types.h"
#include "LightScheduler.h"
#include "TimeService_Fake.h"
#include "TimeService_Os.h"
#include "../LightController/Src/LightController.h"

typedef struct TimeService_FakeType_tag
{
   TimeService_Time Time;
}TimeService_FakeType;

static TimeService_FakeType TimeService_Fake;


void TimeService_Fake_Init()
{
   TimeService_Fake.Time.Day = TIMESERVICE_MONDAY;
   TimeService_Fake.Time.Minute = 0;
}


void TimeService_Os_GetTime(TimeService_Time * const Time)
{
   *Time = TimeService_Fake.Time;
}

void TimeService_Fake_SetStartTime(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Fake.Time.Day = Day;
   TimeService_Fake.Time.Minute = Minute;
}

void TimeService_Fake_RunUntil(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Time StopTime;
   StopTime.Day = Day;
   StopTime.Minute = Minute;

   while ( !TimeService_IsNowEqualTo(&StopTime))
   {
      LightScheduler_MainFunction();
      TimeService_Add(&(TimeService_Fake.Time), 0, 1);
   }
}


void TimeService_Fake_SetDay(TimeService_DayType Day)
{
   TimeService_Fake.Time.Day = Day;
}

void TimeService_Fake_SetMinute(uint16 Minute)
{
   TimeService_Fake.Time.Minute = Minute;
}
