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

typedef struct LightController_InterfaceType_tag LightController_InterfaceType;

typedef void (*LightController_DriverInitFunction)
      (LightController_InterfaceType * const Interface,
            void const * const DriverConfig);


typedef struct
{
   const LightController_DriverInitFunction DriverInit;
   void const * const DriverConfig;
} LightController_ConfigType;

typedef struct
{
   LightController_ConfigType Config[LIGHTCONTROLLER_ID_MAX];
}LightController_MConfigType;




extern void LightController_Init(LightController_MConfigType const * const Config);

extern void LightController_SetDriver(LightController_IdType Id,
      LightController_ConfigType const * const Config);

extern void LightController_On(LightController_IdType Id);

extern void LightController_Off(LightController_IdType Id);

#endif /* LIGHTCONTROLLER_H_ */
