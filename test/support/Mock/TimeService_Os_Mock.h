/*
 * TimeService_Os_Mock.h
 *
 *  Created on: May 29, 2019
 *      Author: reser
 */

#ifndef TEST_SUPPORT_MOCK_TIMESERVICE_OS_MOCK_H__
#define TEST_SUPPORT_MOCK_TIMESERVICE_OS_MOCK_H__

#include "Std_Types.h"
#include "TimeService_Types.h"

extern void TimeService_Os_GetTime_CALLBACK(TimeService_Time* const Time, int cmock_num_calls);

extern TimeService_Time TimeService_Os_Mock_SetTime(TimeService_DayType Day, uint16 Minute);

extern void TimeService_Os_Mock_IncrementTime(void);

#endif /* TEST_SUPPORT_MOCK_TIMESERVICE_OS_MOCK_H__ */
