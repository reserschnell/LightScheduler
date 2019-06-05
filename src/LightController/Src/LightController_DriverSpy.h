/*
 * LightController_Spy.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef LIGHTCONTROLLER_DRIVERSPY_H_
#define LIGHTCONTROLLER_DRIVERSPY_H_

#include "Std_Types.h"
#include "LightController_Driver.h"
#include "LightController.h"
#include "TimeService.h"



typedef struct
{
   uint8 DriverId;
   uint16 CounterMax;
   BOOL TimerActive;
} LightController_DriverSpyConfigType;

typedef struct
{
   LightController_IdType Id;
   LightController_StateType State;
   TimeService_Time Time;
} LightController_DriverSpyEventType;



extern void LightController_DriverSpy_Init(LightController_InterfaceType * const Interface,
      LightController_DriverSpyConfigType const * const Config);

extern LightController_DriverSpyEventType LightController_DriverSpy_GetEvent(uint16 EventNumber);

#endif /* LIGHTCONTROLLER_DRIVERSPY_H_ */
