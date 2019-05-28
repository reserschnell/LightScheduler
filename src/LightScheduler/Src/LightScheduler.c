/*
 * LightScheduler.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#include "LightScheduler.h"

#include "Std_Types.h"
#include "TimeService.h"

struct LightSchedulerDataType_tag
{
   BOOL IsFree;
   LightController_IdType Id;
   LightScheduler_DayType DayRequest;
   uint16 MinuteRequest;
   LightController_StateType StateRequest;
   TimeService_Time NextEventTime;
   BOOL SwitchingDone;
   BOOL IsRandomized;
};

typedef struct LightSchedulerType_tag
{
   LightSchedulerDataType Data[LIGHTSCHEDULER_MAX_EVENTS];
   LightSchedulerMConfigType const * MCfgPtr;
}LightSchedulerType;


static LightSchedulerType LightScheduler;


void LightScheduler_Init(LightSchedulerConfigType const * const ConfigPtr)
{
   LightSchedulerDataType * DataPtr;
   uint16 Id;

   LightScheduler.MCfgPtr = ConfigPtr->MCfgPtr;

   for (Id = 0; Id < LIGHTSCHEDULER_MAX_EVENTS; Id++)
   {
      DataPtr = &(LightScheduler.Data[Id]);
      DataPtr->Id = LIGHTCONTROLLER_ID_UNKNOWN;
      DataPtr->DayRequest = LIGHTSCHEDULER_EVERYDAY;
      DataPtr->MinuteRequest = 0;
      DataPtr->StateRequest = LIGHTCONTROLLER_STATE_OFF;
      DataPtr->NextEventTime.Day = TIMESERVICE_MONDAY;
      DataPtr->NextEventTime.Minute = 0;
      DataPtr->SwitchingDone = FALSE;

      DataPtr->IsFree = TRUE;
      DataPtr->IsRandomized = FALSE;
   }

}


static inline BOOL LightScheduler_lIsDayMatching(
      LightSchedulerDataType const * const DataPtr,
      TimeService_Time const * const Time)
{
   BOOL DayIsMatching = FALSE;

   switch (DataPtr->DayRequest)
   {
      case LIGHTSCHEDULER_EVERYDAY:
         DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_MONDAY:
         if (Time->Day == TIMESERVICE_MONDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_TUESDAY:
         if (Time->Day == TIMESERVICE_TUESDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_WEDNESDAY:
         if (Time->Day == TIMESERVICE_WEDNESDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_THURSDAY:
         if (Time->Day == TIMESERVICE_THURSDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_FRIDAY:
         if (Time->Day == TIMESERVICE_FRIDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_SATURDAY:
         if (Time->Day == TIMESERVICE_SATURDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_SUNDAY:
         if (Time->Day == TIMESERVICE_SUNDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_WEEKEND:
         if (Time->Day == TIMESERVICE_SATURDAY
               || Time->Day == TIMESERVICE_SUNDAY)
            DayIsMatching = TRUE;
         break;

      case LIGHTSCHEDULER_WEEKDAY:
         if (Time->Day == TIMESERVICE_MONDAY
               || Time->Day == TIMESERVICE_TUESDAY
               || Time->Day == TIMESERVICE_WEDNESDAY
               || Time->Day == TIMESERVICE_THURSDAY
               || Time->Day == TIMESERVICE_FRIDAY)
            DayIsMatching = TRUE;
         break;
      default:
         break;
   }

   return (DayIsMatching);
}

static inline void LightScheduler_lSetNextSwitchingTime(LightSchedulerDataType * DataPtr)
{
   sint32 MinuteAdder;
   BOOL NextSwitchingTimeFound = FALSE;
   TimeService_Time SearchTime;
   TimeService_Time Now;
   TimeService_Time NowRandom;
   BOOL SearchInFuture = FALSE;

   if (DataPtr->IsRandomized == TRUE)
   {
      MinuteAdder = LightScheduler.MCfgPtr->GetRandomMinute();
   }
   else
   {
      MinuteAdder = 0;
   }

   TimeService_GetTime(&Now);
   NowRandom = Now;
   TimeService_Add(&NowRandom, 0, -MinuteAdder);

   SearchTime = Now;
   SearchTime.Minute = DataPtr->MinuteRequest;

   do
   {
      if (SearchInFuture == FALSE
            && TimeService_IsLeftLaterThenRight(&SearchTime, &NowRandom))
      {
         SearchInFuture = TRUE;
      }

      if (SearchInFuture
            && LightScheduler_lIsDayMatching(DataPtr, &SearchTime))
      {
         NextSwitchingTimeFound = TRUE;
      }

      if (!NextSwitchingTimeFound)
      {
         TimeService_Add(&SearchTime, 1, 0);
      }
   } while (!NextSwitchingTimeFound);


   TimeService_Add(&SearchTime, 0, MinuteAdder);


   DataPtr->NextEventTime = SearchTime;
}



LightSchedulerDataType * LightScheduler_Create(
      LightController_IdType IdLightController,
      LightScheduler_DayType Day,
      uint16 MinuteOfDay)
{
   LightSchedulerDataType * DataPtr;
   LightSchedulerDataType * ReturnPtr = NULL_PTR;
   uint16 Id;

   for (Id = 0; Id < LIGHTSCHEDULER_MAX_EVENTS; Id++)
   {
      DataPtr = &(LightScheduler.Data[Id]);

      if (DataPtr->IsFree)
      {
         DataPtr->Id = IdLightController;
         DataPtr->DayRequest = Day;
         DataPtr->MinuteRequest = MinuteOfDay;
         DataPtr->StateRequest = LIGHTCONTROLLER_STATE_ON;
         DataPtr->IsFree = FALSE;

         LightScheduler_lSetNextSwitchingTime(DataPtr);

         ReturnPtr = DataPtr;
         break;
      }
   }

   return (ReturnPtr);
}


static inline Std_ReturnType LichtScheduler_lCheck(LightSchedulerDataType * DataPtr)
{
   Std_ReturnType ReturnValue = E_OK;
   if (DataPtr->IsFree)
   {
      ReturnValue = E_NOT_OK;
   }

   return(ReturnValue);
}

Std_ReturnType LightScheduler_TurnOn(LightSchedulerDataType * DataPtr)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(DataPtr);
   if (ReturnValue == E_OK)
      DataPtr->StateRequest = LIGHTCONTROLLER_STATE_ON;

   return(ReturnValue);
}


Std_ReturnType LightScheduler_TurnOff(LightSchedulerDataType * DataPtr)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(DataPtr);
   if (ReturnValue == E_OK)
      DataPtr->StateRequest = LIGHTCONTROLLER_STATE_OFF;

   return (ReturnValue);
}

Std_ReturnType LightScheduler_Remove(LightSchedulerDataType * DataPtr)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(DataPtr);
   if (ReturnValue == E_OK)
      DataPtr->IsFree = TRUE;

   return (ReturnValue);
}

Std_ReturnType LightScheduler_Randomize(LightSchedulerDataType * DataPtr)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(DataPtr);

   if (ReturnValue == E_OK)
   {
      DataPtr->IsRandomized = TRUE;

      LightScheduler_lSetNextSwitchingTime(DataPtr);
   }

   return (ReturnValue);
}



static inline void LightScheduler_lDoLightSwitching(
      LightSchedulerDataType * const DataPtr)
{

   if (DataPtr->StateRequest == LIGHTCONTROLLER_STATE_ON)
   {
      LightController_On(DataPtr->Id);
   }
   else if (DataPtr->StateRequest == LIGHTCONTROLLER_STATE_OFF)
   {
      LightController_Off(DataPtr->Id);
   }

}


static inline void LightScheduler_lDoEventProcessing(
      LightSchedulerDataType * const DataPtr)
{

   if (TimeService_IsNowEqualTo(&(DataPtr->NextEventTime)))
   {

      if (DataPtr->SwitchingDone)
      {
         LightScheduler_lSetNextSwitchingTime(DataPtr);
         DataPtr->SwitchingDone = FALSE;
      }
      else
      {
         LightScheduler_lDoLightSwitching(DataPtr);

         // Reset randomization
         DataPtr->NextEventTime.Minute = DataPtr->MinuteRequest;
         // increment by half a day until next switching day is searched
         TimeService_Add(&DataPtr->NextEventTime, 0, 12*60);

         DataPtr->SwitchingDone = TRUE;
      }


   }
}

void LightScheduler_MainFunction(void)
{
   LightSchedulerDataType * DataPtr;
   uint16 Id;

   for (Id = 0; Id < LIGHTSCHEDULER_MAX_EVENTS; Id++)
   {
      DataPtr = &(LightScheduler.Data[Id]);
      if (!DataPtr->IsFree)
      {
         LightScheduler_lDoEventProcessing(DataPtr);
      }
   }

}
