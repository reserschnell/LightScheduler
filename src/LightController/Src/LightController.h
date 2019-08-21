/*
 * LightController.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef LIGHTCONTROLLER_H_
#define LIGHTCONTROLLER_H_

#include "Std_Types.h"

#include "LightController_Cfg.h"


typedef enum
{
   LIGHTCONTROLLER_STATE_OFF,
   LIGHTCONTROLLER_STATE_ON
} LightController_StateType;

typedef struct LightController_InterfaceTypeTag LightController_InterfaceType;

typedef void (*LightController_DriverInitFunction)
      (LightController_InterfaceType * const Interface,
            uint8 DriverId,
            void const * const DriverConfig);


typedef struct
{
   const uint8 DriverId;
   const LightController_DriverInitFunction DriverInit;
   const void * const DriverConfig;
} LightController_PipConstType;

typedef struct
{
   LightController_PipConstType PipConst[LIGHTCONTROLLER_ID_MAX];
}LightController_ConfigType;




extern void LightController_Init(const LightController_ConfigType * const Config);

extern void LightController_SetDriver(LightController_IdType Id,
      const LightController_PipConstType * const Config);

extern void LightController_On(LightController_IdType Id);

extern void LightController_Off(LightController_IdType Id);

#endif /* LIGHTCONTROLLER_H_ */
