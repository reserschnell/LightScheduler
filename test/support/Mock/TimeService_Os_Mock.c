/*
 * TimeService_Os_Mock.c
 *
 *  Created on: May 29, 2019
 *      Author: reser
 */

#include "TimeService_Os_Mock.h"

#include "unity.h"
#include "mock_TimeService_Os.h"
#include "TimeService.h"


typedef struct
{
   TimeService_Time Time;
}TimeService_OsType;

static TimeService_OsType TimeService_Os;


void TimeService_Os_GetTime_CALLBACK(TimeService_Time* const Time, int cmock_num_calls)
{
   *Time = TimeService_Os.Time;
}



TimeService_Time TimeService_Os_Mock_SetTime(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Time * Time;

   Time = &(TimeService_Os.Time);
   Time->Day = Day;
   Time->Minute = Minute;

   // Experiments to avoid callback
//   TimeService_Os_GetTime_Expect(NULL_PTR);
//   TimeService_Os_GetTime_IgnoreArg_Time();
//   TimeService_Os_GetTime_ReturnThruPtr_Time(Time);
//   TimeService_Os_GetTime_Ignore();

   TimeService_Os.Time = *Time;

   return(*Time);
}


void TimeService_Os_Mock_IncrementTime(void)
{
   TimeService_Time Time;

   TimeService_GetTime(&Time);
   TimeService_Add(&Time, 0, 1);

   TimeService_Os_Mock_SetTime(Time.Day, Time.Minute);

}
