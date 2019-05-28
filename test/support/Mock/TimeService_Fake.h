/*
 * TimeService_Fake.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef TIMESERVICE_FAKE_H_
#define TIMESERVICE_FAKE_H_

#include "Std_Types.h"
#include "TimeService.h"


extern void TimeService_Fake_Init(void);

extern void TimeService_Fake_SetStartTime(TimeService_DayType Day, uint16 Minute);

extern void TimeService_Fake_RunUntil(TimeService_DayType Day, uint16 Minute);

extern void TimeService_Fake_SetDay(TimeService_DayType Day);

extern void TimeService_Fake_SetMinute(uint16 Minute);



#endif /* TIMESERVICE_FAKE_H_ */
