/*
 * LightController_Driver.h
 *
 *  Created on: Jan 30, 2019
 *      Author: reser
 */

#ifndef LIGHTCONTROLLER_DRIVER_H_
#define LIGHTCONTROLLER_DRIVER_H_

#include "Std_Types.h"
#include "LightController.h"

struct LightController_InterfaceTypeTag
{
   void (*DriverOn)(uint8 DriverId);
   void (*DriverOff)(uint8 DriverId);
};



#endif /* LIGHTCONTROLLER_DRIVER_H_ */
