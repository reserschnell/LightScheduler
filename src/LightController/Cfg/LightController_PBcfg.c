/*
 * LightScheduler_Cfg.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "LightController_PBcfg.h"
#include "LightController_DriverSpy.h"
#include "LightController_DriverCount.h"


LightController_DriverCountConfigType LightController_DriverCountConfig =
{
   .PlaceHolder = 0
};


LightController_DriverSpyConfigType LightController_DriverSpyConfig =
{
   .DriverId = 0,
   .CounterMax = 0,
   .TimerActive = 0
};


LightController_MConfigType LightController_Config =
{
   .Config[0] =
   {
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpyConfig
   },
   .Config[1] =
   {
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpyConfig
   },
   .Config[2] =
   {
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpyConfig
   },
   .Config[3] =
   {
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpyConfig
   },
   .Config[4] =
   {
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpyConfig
   },
   .Config[5] =
   {
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpyConfig
   }
};

