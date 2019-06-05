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


extern LightController_DriverSpyEventType Expected;


extern void LightController_DriverSpy_Init(LightController_InterfaceType * const Interface,
      LightController_DriverSpyConfigType const * const Config);

extern void LightController_DriverSpy_CheckEvent(LightController_DriverSpyEventType const * const ExpectedEvent, uint16 NumberGivenEvent);

extern void LightController_DriverSpy_CheckDefault(void);

extern LightController_DriverSpyEventType LightController_DriverSpy_GetDefault(void);

#endif /* LIGHTCONTROLLER_DRIVERSPY_H_ */
