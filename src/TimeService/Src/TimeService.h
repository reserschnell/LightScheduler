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
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight);

extern BOOL TimeService_IsLeftLaterThenRight(
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight);

extern BOOL TimeService_IsLeftEqualToRight(
      const TimeService_Time * const TimeLeft,
      const TimeService_Time * const TimeRight);


extern BOOL TimeService_IsNowEarlierThen(const TimeService_Time * const Time);

extern BOOL TimeService_IsNowEqualTo(const TimeService_Time * const Time);

extern BOOL TimeService_IsNowLaterThen(const TimeService_Time * const Time);

extern BOOL TimeService_IsNowLaterOrEqualTo(const TimeService_Time * const Time);

extern BOOL TimeService_IsNowEarlierOrEqualTo(const TimeService_Time * const Time);


#endif /* TIMESERVICE_H_ */
