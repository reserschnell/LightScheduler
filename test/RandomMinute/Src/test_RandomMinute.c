


#include "unity.h"
#include "Std_Types.h"
#include "RandomMinute.h"
#include "RandomMinute_PBcfg.h"
#include "stdlib.h"
#include "stdio.h"




void setUp(void)
{
   RandomMinute_Init(&RandomMinuteConfig);
   srand(1);
}

void tearDown(void)
{
}



void test_RandomMinute_GetIsInRange(void)
{
   sint16 Minute;
   for (int i = 0; i < 100; i++)
   {
      Minute = RandomMinute_Get();

      TEST_ASSERT_INT16_WITHIN((sint16)RandomMinuteConfig.Bound, 0, Minute);
   }
}


void test_RandomMinute_AllValuesPossible(void)
{
   sint16 Minute;
   const sint16 SizeOfErrorCntr = (sint16)(RandomMinuteConfig.Bound*2 +1);
   sint16 ErrorCntr = 0;
   sint16 ResultCntr[RANDOMMINUTE_BOUND*2 +1] = {0};
   sint16 i;

   for (i = 0; i < 300; i++)
   {
      Minute = RandomMinute_Get();
      TEST_ASSERT_INT16_WITHIN((sint16)RandomMinuteConfig.Bound, 0, Minute);
      ResultCntr[Minute + (sint16)RandomMinuteConfig.Bound]++;
   }
   for (i = 0; i < SizeOfErrorCntr; i++)
   {
      if (ResultCntr[i] == 0)
      {
         ErrorCntr++;
      }
   }
   TEST_ASSERT_EQUAL_INT16(0, ErrorCntr);
}
