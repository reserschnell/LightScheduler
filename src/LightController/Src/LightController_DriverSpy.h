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
   const LightController_IdType LightControllerId;
} LightController_DriverSpy_PipConstType;

typedef struct
{
   const uint8 PlaceHolder;
} LightController_DriverSpy_PipCalibType;



typedef struct
{
   const LightController_DriverSpy_PipConstType PipConst[LIGHTCONTROLLER_DRIVER_SPY_ID_MAX];
   const LightController_DriverSpy_PipCalibType * const PipCalib;
} LightController_DriverSpy_ConfigType;

typedef struct
{
   LightController_IdType LightControllerId;
   LightController_StateType State;
   TimeService_Time Time;
} LightController_DriverSpyEventType;


extern LightController_DriverSpyEventType Expected;


extern void LightController_DriverSpy_Init(LightController_InterfaceType * const Interface,
      uint8 DriverSpyId,
      const LightController_DriverSpy_ConfigType * const Config);

extern void LightController_DriverSpy_DeInit(void);

extern void LightController_DriverSpy_CheckEvent(
      const LightController_DriverSpyEventType * const ExpectedEvent,
      const uint16 NumberGivenEvent);

extern void LightController_DriverSpy_CheckDefault(void);

extern LightController_DriverSpyEventType LightController_DriverSpy_GetDefault(void);

#endif /* LIGHTCONTROLLER_DRIVERSPY_H_ */
