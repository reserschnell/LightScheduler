/*
 * LightScheduler_Cfg.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */


#include "LightController_PBcfg.h"
#include "LightController_DriverSpy.h"
#include "LightController_DriverCount.h"




const LightController_PipConstType LightController_DriverCount_Config =
{
   .DriverId = 0,
   .DriverInit =
      (LightController_DriverInitFunction)LightController_DriverCount_Init,
   .DriverConfig = NULL_PTR
};



static const LightController_DriverSpy_PipCalibType
      LightController_DriverSpy_PipCalib[LIGHTCONTROLLER_DRIVER_SPY_ID_MAX] =
{
   {
      0
   },
   {
      0
   },
   {
      0
   },
   {
      0
   },
   {
      0
   },
   {
      0
   }
};

const LightController_DriverSpy_ConfigType LightController_DriverSpy_Config =
{
   .PipConst =
   {
      {
         LIGHTCONTROLLER_BATHROOM,
      },
      {
         LIGHTCONTROLLER_LIVINGROOM,
      },
      {
         LIGHTCONTROLLER_KITCHEN,
      },
      {
         LIGHTCONTROLLER_BEDROOM,
      },
      {
         LIGHTCONTROLLER_CHILD1,
      },
      {
         LIGHTCONTROLLER_CHILD2
      }
   },
   .PipCalib = &LightController_DriverSpy_PipCalib[0]
};



const LightController_ConfigType LightController_Config =
{
   .PipConst[0] =
   {
      .DriverId = 0,
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpy_Config
   },
   .PipConst[1] =
   {
      .DriverId = 1,
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpy_Config
   },
   .PipConst[2] =
   {
      .DriverId = 2,
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpy_Config
   },
   .PipConst[3] =
   {
      .DriverId = 3,
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpy_Config
   },
   .PipConst[4] =
   {
      .DriverId = 4,
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpy_Config
   },
   .PipConst[5] =
   {
      .DriverId = 5,
      .DriverInit =
            (LightController_DriverInitFunction)LightController_DriverSpy_Init,
      .DriverConfig = &LightController_DriverSpy_Config
   }
};

