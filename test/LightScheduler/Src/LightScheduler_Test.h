/*
 * LightScheduler_Test.h
 *
 *  Created on: May 28, 2019
 *      Author: reser
 */

#ifndef LIGHTSCHEDULER_TEST_H_
#define LIGHTSCHEDULER_TEST_H_


#include "TimeService_Types.h"
#include "LightController_DriverSpy.h"



extern void LightScheduler_Test_SetUp(void);

extern void LightScheduler_Test_RunUntil(TimeService_DayType Day, uint16 Minute);


#endif /* LIGHTSCHEDULER_TEST_H_ */
