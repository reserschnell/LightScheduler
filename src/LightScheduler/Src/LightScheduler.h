/*
 * LightScheduler.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef SRC_LIGHTSCHEDULER_H_
#define SRC_LIGHTSCHEDULER_H_

#include "Std_Types.h"

#include "LightController_Cfg.h"
#include "LightController.h"
#include "LightScheduler_Cfg.h"

typedef enum LightScheduler_DayType_tag
{
      LIGHTSCHEDULER_EVERYDAY = 0,
      LIGHTSCHEDULER_MONDAY,
      LIGHTSCHEDULER_TUESDAY,
      LIGHTSCHEDULER_WEDNESDAY,
      LIGHTSCHEDULER_THURSDAY,
      LIGHTSCHEDULER_FRIDAY,
      LIGHTSCHEDULER_SATURDAY,
      LIGHTSCHEDULER_SUNDAY,
      LIGHTSCHEDULER_WEEKEND,
      LIGHTSCHEDULER_WEEKDAY
} LightScheduler_DayType;

typedef struct LightSchedulerMConfigType_tag
{
   sint16 (* GetRandomMinute)(void);
}LightSchedulerMConfigType;

typedef struct LightSchedulerConfigType_tag
{
   LightSchedulerMConfigType const *MCfgPtr;
}LightSchedulerConfigType;


typedef struct LightSchedulerDataType_tag LightSchedulerDataType;


extern void LightScheduler_Init(LightSchedulerConfigType const * const ConfigPtr);


extern LightSchedulerDataType * LightScheduler_Create(
      LightController_IdType Id,
      LightScheduler_DayType Day,
      uint16 MinuteOfDay);

extern Std_ReturnType LightScheduler_TurnOn(LightSchedulerDataType * DataPtr);


extern Std_ReturnType LightScheduler_TurnOff(LightSchedulerDataType * DataPtr);


extern Std_ReturnType LightScheduler_Remove(LightSchedulerDataType * DataPtr);


extern Std_ReturnType LightScheduler_Randomize(LightSchedulerDataType * DataPtr);


extern void LightScheduler_MainFunction(void);






#endif /* SRC_LIGHTSCHEDULER_H_ */
