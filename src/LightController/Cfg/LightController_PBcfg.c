/*
 * LightScheduler_Cfg.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "LightController_PBcfg.h"
#include "LightController_DriverSpy.h"


LightController_DriverSpyConfigType LightController_DriverSpyConfig =
{
   0,
   0,
   0
};


LightController_MConfigType LightController_Config =
{
   {
      {
         (LightController_DriverInitFunction)LightController_DriverSpy_Init,
         &LightController_DriverSpyConfig
      },
      {
         (LightController_DriverInitFunction)LightController_DriverSpy_Init,
         &LightController_DriverSpyConfig
      },
      {
         (LightController_DriverInitFunction)LightController_DriverSpy_Init,
         &LightController_DriverSpyConfig
      },
      {
         (LightController_DriverInitFunction)LightController_DriverSpy_Init,
         &LightController_DriverSpyConfig
      },
      {
         (LightController_DriverInitFunction)LightController_DriverSpy_Init,
         &LightController_DriverSpyConfig
      },
      {
         (LightController_DriverInitFunction)LightController_DriverSpy_Init,
         &LightController_DriverSpyConfig
      }
   }
};

