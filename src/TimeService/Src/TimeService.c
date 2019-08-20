/*
 * TimeService.c
 *
 *  Created on: Dec 17, 2018
 *      Author: reser
 */
#include "TimeService.h"
#include "TimeService_Os.h"

#define TIMESERVICE_MAX_MINUTES ((sint16)(24*60))
#define TIMESERVICE_MAX_DAYS ((sint16)(7))


void TimeService_GetTime(TimeService_Time * const Time)
{
   TimeService_Os_GetTime(Time);
}


void TimeService_Add(
      TimeService_Time * const Time, sint8 Days, sint16 Minutes)
{
   sint16 DayIntSint16;
   sint16 MinuteSint16;
   sint16 MinuteSint16Modulo;
   sint16 DayAdder = 0;

   MinuteSint16 = (sint16)Time->Minute;
   MinuteSint16 += Minutes;
   MinuteSint16Modulo = MinuteSint16 % TIMESERVICE_MAX_MINUTES;
   if (MinuteSint16Modulo < 0)
   {
      MinuteSint16Modulo += TIMESERVICE_MAX_MINUTES;
      DayAdder = -1;
   }

   Time->Minute = (uint16)MinuteSint16Modulo;

   DayAdder += MinuteSint16/TIMESERVICE_MAX_MINUTES;

   DayIntSint16 = (sint16)Time->Day;
   DayIntSint16 += Days + DayAdder;
   DayIntSint16 %= TIMESERVICE_MAX_DAYS;
   if (DayIntSint16 < 0)
   {
      DayIntSint16 += TIMESERVICE_MAX_DAYS;
   }

   Time->Day = (TimeService_DayType)DayIntSint16;

}

static inline sint8 TimeService_lGetLeftRelativeToRight(
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight)
{
   sint8 LeftRelativeToRight = -1; // TimeLeft is earlier then TimeRight

   sint16 DayAdder;
   sint16 MinuteAdder;
   TimeService_Time TimeLeftNorm;
   TimeService_Time TimeRightNorm;


   TimeRightNorm.Day = TIMESERVICE_THURSDAY;
   TimeRightNorm.Minute = 12*60;


   DayAdder = (sint16)TimeRightNorm.Day - (sint16)TimeRight->Day;
   MinuteAdder = (sint16)TimeRightNorm.Minute - (sint16)TimeRight->Minute;

   TimeLeftNorm = *TimeLeft;
   TimeService_Add(&TimeLeftNorm, DayAdder, MinuteAdder);


   if (TimeLeftNorm.Day == TimeRightNorm.Day)
   {
      if (TimeLeftNorm.Minute == TimeRightNorm.Minute)
      {
         LeftRelativeToRight = 0;
      }
      else if (TimeLeftNorm.Minute > TimeRightNorm.Minute)
      {
         LeftRelativeToRight = 1;
      }
   }
   else if (TimeLeftNorm.Day > TimeRightNorm.Day)
   {
      LeftRelativeToRight = 1;
   }

   return (LeftRelativeToRight);
}





BOOL TimeService_IsLeftEarlierThenRight(
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight)
{
   BOOL ReturnValue = FALSE;
   sint8 LeftRelativeToRight;

   LeftRelativeToRight = TimeService_lGetLeftRelativeToRight(TimeLeft, TimeRight);
   ReturnValue = LeftRelativeToRight == -1;

   return (ReturnValue);
}


BOOL TimeService_IsLeftLaterThenRight(
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight)
{
   BOOL ReturnValue = FALSE;
   sint8 LeftRelativeToRight;

   LeftRelativeToRight = TimeService_lGetLeftRelativeToRight(TimeLeft, TimeRight);
   ReturnValue = LeftRelativeToRight == 1;

   return (ReturnValue);
}


BOOL TimeService_IsLeftEqualToRight(
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight)
{
   BOOL ReturnValue = FALSE;
   sint8 LeftRelativeToRight;

   LeftRelativeToRight = TimeService_lGetLeftRelativeToRight(TimeLeft, TimeRight);
   ReturnValue = LeftRelativeToRight == 0;

   return (ReturnValue);
}


BOOL TimeService_IsNowEarlierThen(const TimeService_Time * const Time)
{
   BOOL ReturnValue;
   TimeService_Time Now;

   TimeService_GetTime(&Now);

   ReturnValue = TimeService_IsLeftEarlierThenRight(&Now, Time);

   return (ReturnValue);
}

BOOL TimeService_IsNowEqualTo(const TimeService_Time * const Time)
{
   BOOL ReturnValue;
   TimeService_Time Now;

   TimeService_GetTime(&Now);

   ReturnValue = TimeService_IsLeftEqualToRight(&Now, Time);

   return (ReturnValue);
}

BOOL TimeService_IsNowLaterThen(const TimeService_Time * const Time)
{
   BOOL ReturnValue;
   TimeService_Time Now;

   TimeService_GetTime(&Now);

   ReturnValue = TimeService_IsLeftLaterThenRight(&Now, Time);

   return (ReturnValue);
}


BOOL TimeService_IsNowLaterOrEqualTo(const TimeService_Time * const Time)
{
   BOOL ReturnValue;

   ReturnValue = !TimeService_IsNowEarlierThen(Time);

   return (ReturnValue);
}


BOOL TimeService_IsNowEarlierOrEqualTo(const TimeService_Time * const Time)
{
   BOOL ReturnValue;

   ReturnValue = !TimeService_IsNowLaterThen(Time);

   return (ReturnValue);
}


