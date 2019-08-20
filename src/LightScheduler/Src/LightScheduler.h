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

typedef enum
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

typedef struct
{
   sint16 (* GetRandomMinute)(void);
}LightScheduler_SpConstType;

typedef struct
{
   const LightScheduler_SpConstType * SpConst;
}LightScheduler_ConfigType;


typedef struct LightScheduler_SelfTypeTag LightScheduler_SelfType;


extern void LightScheduler_Init(const LightScheduler_ConfigType * const Config);


extern LightScheduler_SelfType * LightScheduler_Create(
      LightController_IdType Id,
      LightScheduler_DayType Day,
      uint16 MinuteOfDay);

extern Std_ReturnType LightScheduler_TurnOn(LightScheduler_SelfType * const Self);


extern Std_ReturnType LightScheduler_TurnOff(LightScheduler_SelfType * const Self);


extern Std_ReturnType LightScheduler_Remove(LightScheduler_SelfType * const Self);


extern Std_ReturnType LightScheduler_Randomize(LightScheduler_SelfType * const Self);


extern void LightScheduler_MainFunction(void);






#endif /* SRC_LIGHTSCHEDULER_H_ */
