/*
 * LightController_Spy.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef LIGHTCONTROLLER_DRIVERCOUNT_H_
#define LIGHTCONTROLLER_DRIVERCOUNT_H_

#include "Std_Types.h"
#include "LightController_Driver.h"




extern void LightController_DriverCount_Init(LightController_InterfaceType * const Interface,
      uint8 DriverCountId,
      const void * const Config);

extern void LightController_DriverCount_DeInit(void);

extern uint16 LightController_DriverCount_GetEventCntr(void);

#endif /* LIGHTCONTROLLER_DRIVERCOUNT_H_ */
