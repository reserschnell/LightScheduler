/*
 * TimeService.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

#include "TimeService_Types.h"


extern void TimeService_GetTime(TimeService_Time * const Time);


extern void TimeService_Add(
      TimeService_Time * const Time, sint8 Days, sint16 Minutes);


extern BOOL TimeService_IsLeftEarlierThenRight(
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight);

extern BOOL TimeService_IsLeftLaterThenRight(
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight);

extern BOOL TimeService_IsLeftEqualToRight(
      TimeService_Time * const TimeLeft,
      TimeService_Time * const TimeRight);


extern BOOL TimeService_IsNowEarlierThen(TimeService_Time * const Time);

extern BOOL TimeService_IsNowEqualTo(TimeService_Time * const Time);

extern BOOL TimeService_IsNowLaterThen(TimeService_Time * const Time);

extern BOOL TimeService_IsNowLaterOrEqualTo(TimeService_Time * const Time);

extern BOOL TimeService_IsNowEarlierOrEqualTo(TimeService_Time * const Time);


#endif /* TIMESERVICE_H_ */
