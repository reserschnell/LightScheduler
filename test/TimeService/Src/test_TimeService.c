


#include "unity.h"
#include "Std_Types.h"
#include "TimeService.h"
//#include "TimeService_Fake.h"
#include "LightScheduler.h"
#include "LightController.h"
#include "mock_TimeService_Os.h"



static uint16 const MinutesPerDay = 24*60;

static TimeService_Time SetTime(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Time TestTime;
   TestTime.Day = Day;
   TestTime.Minute = Minute;

   TimeService_Os_GetTime_Expect(&TestTime);
   TimeService_Os_GetTime_IgnoreArg_Time();
   TimeService_Os_GetTime_ReturnMemThruPtr_Time(&TestTime, sizeof(TestTime));

   return(TestTime);
}


void setUp(void)
{

}

void tearDown(void)
{
}



void test_TimeService_Add_Monday2TuesdayByMinute(void)
{

   TimeService_Time TimeNow;
   uint16 const MinuteNow = MinutesPerDay-1;

   TimeNow.Day = TIMESERVICE_MONDAY;
   TimeNow.Minute = MinuteNow;

   TimeService_Add(&TimeNow, 0, 1);

   TEST_ASSERT_EQUAL(TIMESERVICE_TUESDAY, TimeNow.Day);
   TEST_ASSERT_EQUAL_UINT16(0, TimeNow.Minute);
}

void test_TimeService_Add_Monday2TuesdayByDay(void)
{

   TimeService_Time TimeNow;
   uint16 const MinuteNow = MinutesPerDay-1;

   TimeNow.Day = TIMESERVICE_MONDAY;
   TimeNow.Minute = MinuteNow;

   TimeService_Add(&TimeNow, 1, 0);

   TEST_ASSERT_EQUAL(TIMESERVICE_TUESDAY, TimeNow.Day);
   TEST_ASSERT_EQUAL_UINT16(MinuteNow, TimeNow.Minute);
}

void test_TimeService_Add_Monday2SundayByMinute(void)
{
   TimeService_Time TimeNow;
   uint16 const MinuteNow = MinutesPerDay-1;

   TimeNow.Day = TIMESERVICE_MONDAY;
   TimeNow.Minute = MinuteNow;

   TimeService_Add(&TimeNow, 0, -(sint16)MinutesPerDay);

   TEST_ASSERT_EQUAL(TIMESERVICE_SUNDAY, TimeNow.Day);
   TEST_ASSERT_EQUAL_UINT16(MinuteNow, TimeNow.Minute);
}


void test_TimeService_Add_Monday2SundayByDay(void)
{
   TimeService_Time TimeNow;
   uint16 const MinuteNow = MinutesPerDay-1;

   TimeNow.Day = TIMESERVICE_MONDAY;
   TimeNow.Minute = MinuteNow;

   TimeService_Add(&TimeNow, -1, 0);


   TEST_ASSERT_EQUAL(TIMESERVICE_SUNDAY, TimeNow.Day);
   TEST_ASSERT_EQUAL_UINT16(MinuteNow, TimeNow.Minute);
}


void test_TimeService_Add_Monday2WednesdayByDayAndMinute(void)
{
   TimeService_Time TimeNow;
   uint16 const MinuteNow = MinutesPerDay-1;

   TimeNow.Day = TIMESERVICE_MONDAY;
   TimeNow.Minute = MinuteNow;

   TimeService_Add(&TimeNow, 8, (sint16)MinutesPerDay);

   TEST_ASSERT_EQUAL(TIMESERVICE_WEDNESDAY, TimeNow.Day);
   TEST_ASSERT_EQUAL_UINT16(MinuteNow, TimeNow.Minute);
}


void test_TimeService_Add_Monday2SaturdayByDayAndMinute(void)
{
   TimeService_Time TimeNow;
   uint16 const MinuteNow = MinutesPerDay-1;

   TimeNow.Day = TIMESERVICE_MONDAY;
   TimeNow.Minute = MinuteNow;

   TimeService_Add(&TimeNow, -8, -(sint16)MinutesPerDay);

   TEST_ASSERT_EQUAL(TIMESERVICE_SATURDAY, TimeNow.Day);
   TEST_ASSERT_EQUAL_UINT16(MinuteNow, TimeNow.Minute);
}


void test_TimeService_IsNowEqualTo(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = MinutesPerDay-1;

   TestTime = SetTime(TIMESERVICE_MONDAY, TestMinute);

   TEST_ASSERT_TRUE(TimeService_IsNowEqualTo(&TestTime));
}

void test_TimeService_IsLaterThenNowSameDay(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = MinutesPerDay-1;

   TestTime = SetTime(TIMESERVICE_TUESDAY, TestMinute);

   TestTime.Minute++;
   TEST_ASSERT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
}


void test_TimeService_IsLaterThenNowNextDay(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = MinutesPerDay-1;

   TestTime = SetTime(TIMESERVICE_TUESDAY, TestMinute);

   TestTime.Day = TIMESERVICE_WEDNESDAY;

   TEST_ASSERT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
}


void test_TimeService_IsLaterThenNowPlus3Days(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = MinutesPerDay-1;

   TestTime = SetTime(TIMESERVICE_TUESDAY, TestMinute);

   TestTime.Day = TIMESERVICE_FRIDAY;

   TEST_ASSERT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
}


void test_TimeService_IsLaterThenNowMinus4Days(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = MinutesPerDay-1;

   TestTime = SetTime(TIMESERVICE_SATURDAY, TestMinute);

   TestTime.Day = TIMESERVICE_TUESDAY;

   TEST_ASSERT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
}


void test_TimeService_IsEarlierThenNowSameDay(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = 0;

   TestTime = SetTime(TIMESERVICE_TUESDAY, TestMinute+1);

   TestTime.Minute--;

   TEST_ASSERT_TRUE(TimeService_IsNowLaterThen(&TestTime));
}


void test_TimeService_IsEarlierThenNowPreviousDay(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = 0;

   TestTime = SetTime(TIMESERVICE_WEDNESDAY, TestMinute);

   TestTime.Day = TIMESERVICE_TUESDAY;

   TEST_ASSERT_TRUE(TimeService_IsNowLaterThen(&TestTime));
}


void test_TimeService_IsEarlierThenNowMinus3Days(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = 0;

   TestTime = SetTime(TIMESERVICE_FRIDAY, TestMinute);

   TestTime.Day = TIMESERVICE_TUESDAY;

   TEST_ASSERT_TRUE(TimeService_IsNowLaterThen(&TestTime));
}


void test_TimeService_IsEarlierThenNowPlus4Days(void)
{
   TimeService_Time TestTime;
   uint16 const TestMinute = 0;

   TestTime = SetTime(TIMESERVICE_TUESDAY, TestMinute);

   TestTime.Day = TIMESERVICE_SATURDAY;

   TEST_ASSERT_TRUE(TimeService_IsNowLaterThen(&TestTime));
}

