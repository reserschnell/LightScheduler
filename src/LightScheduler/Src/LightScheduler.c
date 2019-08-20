/*
 * LightScheduler.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#include "LightScheduler.h"

#include "Std_Types.h"
#include "TimeService.h"

struct LightScheduler_SelfTypeTag
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

typedef struct
{
   LightScheduler_SelfType Self[LIGHTSCHEDULER_MAX_EVENTS];
   LightScheduler_SpConstType const * SpConst;
}LightScheduler_Type;


static LightScheduler_Type LightScheduler;


void LightScheduler_Init(const LightScheduler_ConfigType * const Config)
{
   LightScheduler_SelfType * Self;
   uint16 Id;

   LightScheduler.SpConst = Config->SpConst;

   for (Id = 0; Id < LIGHTSCHEDULER_MAX_EVENTS; Id++)
   {
      Self = &(LightScheduler.Self[Id]);
      Self->Id = LIGHTCONTROLLER_ID_UNKNOWN;
      Self->DayRequest = LIGHTSCHEDULER_EVERYDAY;
      Self->MinuteRequest = 0;
      Self->StateRequest = LIGHTCONTROLLER_STATE_OFF;
      Self->NextEventTime.Day = TIMESERVICE_MONDAY;
      Self->NextEventTime.Minute = 0;
      Self->SwitchingDone = FALSE;

      Self->IsFree = TRUE;
      Self->IsRandomized = FALSE;
   }

}


static inline BOOL LightScheduler_lIsDayMatching(
      const LightScheduler_SelfType * const Self,
      const TimeService_Time * const Time)
{
   BOOL DayIsMatching = FALSE;

   switch (Self->DayRequest)
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



static inline void LightScheduler_lInitSearchTime(
      LightScheduler_SelfType * const Self,
      TimeService_Time * const SearchTime,
      sint32 RandomMinute)
{

   TimeService_Time StartOfSearch;

   TimeService_GetTime(&StartOfSearch);

   if (Self->SwitchingDone)
   {
      // Ensures that a light switches only once a day
      TimeService_Add(&StartOfSearch, 0, 12*60);
      Self->SwitchingDone = FALSE;
   }
   else
   {
      TimeService_Add(&StartOfSearch, 0, -RandomMinute);
   }

   SearchTime->Day = StartOfSearch.Day;
   SearchTime->Minute = Self->MinuteRequest;

   if (TimeService_IsLeftEarlierThenRight(SearchTime, &StartOfSearch))
   {
      TimeService_Add(SearchTime, 1, 0);
   }
}


static inline void LightScheduler_lSetNextSwitchingTime(
      LightScheduler_SelfType * const Self)
{
   sint32 RandomMinute = 0;
   TimeService_Time SearchTime;

   if (Self->IsRandomized == TRUE)
   {
      RandomMinute = LightScheduler.SpConst->GetRandomMinute();
   }

   LightScheduler_lInitSearchTime(Self, &SearchTime, RandomMinute);

   while(!LightScheduler_lIsDayMatching(Self, &SearchTime))
   {
      TimeService_Add(&SearchTime, 1, 0);
   }

   TimeService_Add(&SearchTime, 0, RandomMinute);

   Self->NextEventTime = SearchTime;
}



LightScheduler_SelfType * LightScheduler_Create(
      LightController_IdType IdLightController,
      LightScheduler_DayType Day,
      uint16 MinuteOfDay)
{
   LightScheduler_SelfType * Self;
   LightScheduler_SelfType * ReturnPtr = NULL_PTR;
   uint16 Id;

   for (Id = 0; Id < LIGHTSCHEDULER_MAX_EVENTS; Id++)
   {
      Self = &(LightScheduler.Self[Id]);

      if (Self->IsFree)
      {
         Self->Id = IdLightController;
         Self->DayRequest = Day;
         Self->MinuteRequest = MinuteOfDay;
         Self->StateRequest = LIGHTCONTROLLER_STATE_ON;
         Self->SwitchingDone = FALSE;
         Self->IsFree = FALSE;

         LightScheduler_lSetNextSwitchingTime(Self);

         ReturnPtr = Self;
         break;
      }
   }

   return (ReturnPtr);
}


static inline Std_ReturnType LichtScheduler_lCheck(
      const LightScheduler_SelfType * const Self)
{
   Std_ReturnType ReturnValue = E_OK;
   if (Self->IsFree)
   {
      ReturnValue = E_NOT_OK;
   }

   return(ReturnValue);
}

Std_ReturnType LightScheduler_TurnOn(LightScheduler_SelfType * const Self)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(Self);
   if (ReturnValue == E_OK)
   {
      Self->StateRequest = LIGHTCONTROLLER_STATE_ON;
   }

   return(ReturnValue);
}


Std_ReturnType LightScheduler_TurnOff(LightScheduler_SelfType * const Self)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(Self);
   if (ReturnValue == E_OK)
      Self->StateRequest = LIGHTCONTROLLER_STATE_OFF;

   return (ReturnValue);
}

Std_ReturnType LightScheduler_Remove(LightScheduler_SelfType * const Self)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(Self);
   if (ReturnValue == E_OK)
      Self->IsFree = TRUE;

   return (ReturnValue);
}

Std_ReturnType LightScheduler_Randomize(LightScheduler_SelfType * const Self)
{
   Std_ReturnType ReturnValue;

   ReturnValue = LichtScheduler_lCheck(Self);

   if (ReturnValue == E_OK)
   {
      Self->IsRandomized = TRUE;

      LightScheduler_lSetNextSwitchingTime(Self);
   }

   return (ReturnValue);
}



static inline void LightScheduler_lDoLightSwitching(
      LightScheduler_SelfType * const Self)
{

   if (Self->StateRequest == LIGHTCONTROLLER_STATE_ON)
   {
      LightController_On(Self->Id);
   }
   else if (Self->StateRequest == LIGHTCONTROLLER_STATE_OFF)
   {
      LightController_Off(Self->Id);
   }

   Self->SwitchingDone = TRUE;

}


static inline void LightScheduler_lDoEventProcessing(
      LightScheduler_SelfType * const Self)
{

   if (TimeService_IsNowEqualTo(&(Self->NextEventTime)))
   {

      LightScheduler_lDoLightSwitching(Self);
      LightScheduler_lSetNextSwitchingTime(Self);
   }
}

void LightScheduler_MainFunction(void)
{
   LightScheduler_SelfType * Self;
   uint16 Id;

   for (Id = 0; Id < LIGHTSCHEDULER_MAX_EVENTS; Id++)
   {
      Self = &(LightScheduler.Self[Id]);
      if (!Self->IsFree)
      {
         LightScheduler_lDoEventProcessing(Self);
      }
   }

}
