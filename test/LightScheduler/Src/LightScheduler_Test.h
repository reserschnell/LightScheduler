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


extern LightController_DriverSpyEventType Expected;


extern void LightScheduler_Test_SetUp(void);

extern void LightScheduler_Test_RunUntil(TimeService_DayType Day, uint16 Minute);

extern void LightScheduler_Test_CheckEvent(LightController_DriverSpyEventType const * const ExpectedEvent, uint16 NumberGivenEvent);

extern void LightScheduler_Test_CheckDefault(void);


#endif /* LIGHTSCHEDULER_TEST_H_ */
