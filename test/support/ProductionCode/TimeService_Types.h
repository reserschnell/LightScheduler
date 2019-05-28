/*
 * TimeService.h
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#ifndef TIMESERVICE_TYPES_H_
#define TIMESERVICE_TYPES_H_

#include "Std_Types.h"

typedef enum TimeService_DayType_tag
{
      TIMESERVICE_MONDAY = 0,
      TIMESERVICE_TUESDAY,
      TIMESERVICE_WEDNESDAY,
      TIMESERVICE_THURSDAY,
      TIMESERVICE_FRIDAY,
      TIMESERVICE_SATURDAY,
      TIMESERVICE_SUNDAY
} TimeService_DayType;


typedef struct TimeService_Time_tag
{
   TimeService_DayType Day;
   uint16 Minute;
} TimeService_Time;


#endif /* TIMESERVICE_TYPES_H_ */
