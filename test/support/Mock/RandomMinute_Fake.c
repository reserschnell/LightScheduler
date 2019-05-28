/*
 * TimeService_Fake.c
 *
 *  Created on: Nov 18, 2018
 *      Author: reser
 */

#include "Std_Types.h"
#include "RandomMinute_Fake.h"

typedef struct RandomMinute_FakeType_tag
{
   sint16 RandomMinuteStart;
   sint16 RandomMinute;
   sint16 IncrementMinute;
}RandomMinute_FakeType;

RandomMinute_FakeType RandomMinute_Fake;



void RandomMinute_Fake_SetFirstAndIncrement(
      sint16 RandomMinute, sint16 IncrementMinute)
{
   RandomMinute_Fake.RandomMinuteStart = RandomMinute;
   RandomMinute_Fake.RandomMinute = RandomMinute;
   RandomMinute_Fake.IncrementMinute = IncrementMinute;
}



sint16 RandomMinute_Fake_Get(void)
{
   sint16 RandomMinuteReturn = RandomMinute_Fake.RandomMinute;
   RandomMinute_Fake.RandomMinute += RandomMinute_Fake.IncrementMinute;
   return(RandomMinuteReturn);
}
