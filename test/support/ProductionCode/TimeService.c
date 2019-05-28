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
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight)
{
   sint8 LeftRelativeToRight = -1; // TimeLeft is earlier then TimeRight
   BOOL DayIsEqual;
   TimeService_Time TimeRightPlusHalfWeek;


   DayIsEqual = TimeRight->Day == TimeLeft->Day;


   if (DayIsEqual
         && TimeRight->Minute == TimeLeft->Minute)
   {
      LeftRelativeToRight = 0;
   }
   else
   {

      if (DayIsEqual)
      {
         // TimeLeft is older then TimeRight
         if (TimeLeft->Minute > TimeRight->Minute)
         {
            LeftRelativeToRight = 1;
         }
      }
      else
      {
         TimeRightPlusHalfWeek = *TimeRight;
         TimeService_Add(&TimeRightPlusHalfWeek, 3, 0);

         // No weekday overflow in the next half week
         if (TimeRight->Day < TimeRightPlusHalfWeek.Day)
         {
            if (TimeLeft->Day > TimeRight->Day
                  && TimeLeft->Day <= TimeRightPlusHalfWeek.Day)
            {
               LeftRelativeToRight = 1;
            }
         }
         else
         { // Weekday overflow in the next half week
            if (TimeLeft->Day > TimeRight->Day
                  || TimeLeft->Day <= TimeRightPlusHalfWeek.Day)
            {
               LeftRelativeToRight = 1;
            }

         }
      }
   }

   return (LeftRelativeToRight);
}





BOOL TimeService_IsLeftEarlierThenRight(
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight)
{
   BOOL ReturnValue = FALSE;
   sint8 LeftRelativeToRight;

   LeftRelativeToRight = TimeService_lGetLeftRelativeToRight(TimeLeft, TimeRight);
   ReturnValue = LeftRelativeToRight == -1;

   return (ReturnValue);
}


BOOL TimeService_IsLeftLaterThenRight(
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight)
{
   BOOL ReturnValue = FALSE;
   sint8 LeftRelativeToRight;

   LeftRelativeToRight = TimeService_lGetLeftRelativeToRight(TimeLeft, TimeRight);
   ReturnValue = LeftRelativeToRight == 1;

   return (ReturnValue);
}


BOOL TimeService_IsLeftEqualToRight(
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight)
{
   BOOL ReturnValue = FALSE;
   sint8 LeftRelativeToRight;

   LeftRelativeToRight = TimeService_lGetLeftRelativeToRight(TimeLeft, TimeRight);
   ReturnValue = LeftRelativeToRight == 0;

   return (ReturnValue);
}


BOOL TimeService_IsNowEarlierThen(TimeService_Time * const Time)
{
   BOOL ReturnValue;
   TimeService_Time Now;

   TimeService_GetTime(&Now);

   ReturnValue = TimeService_IsLeftEarlierThenRight(&Now, Time);

   return (ReturnValue);
}

BOOL TimeService_IsNowEqualTo(TimeService_Time * const Time)
{
   BOOL ReturnValue;
   TimeService_Time Now;

   TimeService_GetTime(&Now);

   ReturnValue = TimeService_IsLeftEqualToRight(&Now, Time);

   return (ReturnValue);
}

BOOL TimeService_IsNowLaterThen(TimeService_Time * const Time)
{
   BOOL ReturnValue;
   TimeService_Time Now;

   TimeService_GetTime(&Now);

   ReturnValue = TimeService_IsLeftLaterThenRight(&Now, Time);

   return (ReturnValue);
}


BOOL TimeService_IsNowLaterOrEqualTo(TimeService_Time * const Time)
{
   BOOL ReturnValue;

   ReturnValue = !TimeService_IsNowEarlierThen(Time);

   return (ReturnValue);
}


BOOL TimeService_IsNowEarlierOrEqualTo(TimeService_Time * const Time)
{
   BOOL ReturnValue;

   ReturnValue = !TimeService_IsNowLaterThen(Time);

   return (ReturnValue);
}


