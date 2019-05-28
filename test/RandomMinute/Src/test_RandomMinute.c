


#include "unity.h"
#include "Std_Types.h"
#include "RandomMinute.h"
#include "RandomMinute_PBcfg.h"
#include "stdlib.h"


#define TEST_RANDOMMINUTE_NUMBER_OF_ELEMENTS (RANDOMMINUTE_BOUND*2+1)

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
   BOOL ValuePossible[TEST_RANDOMMINUTE_NUMBER_OF_ELEMENTS] = {FALSE};
   sint16 i;

   for (i = 0; i < 300; i++)
   {
      Minute = RandomMinute_Get();
      TEST_ASSERT_INT16_WITHIN((sint16)RandomMinuteConfig.Bound, 0, Minute);
      ValuePossible[Minute + (sint16)RandomMinuteConfig.Bound] = TRUE;
   }

   TEST_ASSERT_EACH_EQUAL_INT(TRUE, ValuePossible, TEST_RANDOMMINUTE_NUMBER_OF_ELEMENTS);
}
