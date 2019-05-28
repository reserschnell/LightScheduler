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


#define NumberOfEvents 10

extern TimeService_Time StartTime;
extern TimeService_Time StopTime;
extern TimeService_Time EventTime[NumberOfEvents];
extern TimeService_Time ExpectedEventTime[NumberOfEvents];

extern LightController_DriverSpyEventType Expected;

extern LightController_DriverSpyEventType const Default;


extern void LightScheduler_Test_SetUp(void);

extern void LightScheduler_Test_CheckEvent(LightController_DriverSpyEventType const * const ExpectedEvent, uint16 NumberGivenEvent);


#endif /* LIGHTSCHEDULER_TEST_H_ */
