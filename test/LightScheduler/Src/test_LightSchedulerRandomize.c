
#include "unity.h"
#include "LightScheduler_Test.h"
#include "RandomMinute_Fake.h"

#include "LightScheduler_PBcfg.h"
#include "LightScheduler.h"
#include "LightController_PBcfg.h"
#include "RandomMinute_PBcfg.h"
#include "RandomMinute.h"
#include "LightController_DriverSpy.h"
#include "TimeService_Os_Mock.h"
#include "mock_TimeService_Os.h"


TEST_FILE("LightController.c")
TEST_FILE("TimeService.c")


LightSchedulerMConfigType const LightScheduler_FakeMConfig =
{
      RandomMinute_Fake_Get
};

LightSchedulerConfigType const LightScheduler_FakeConfig =
{
      &LightScheduler_FakeMConfig
};


void setUp(void)
{
   
   LightScheduler_Test_SetUp();

   LightScheduler_Init(&LightScheduler_FakeConfig);
}

void tearDown(void)
{
   LightScheduler_Test_CheckDefault();
}


void test_LightSchedulerRandomize_TurnsOnEarly(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(-10, 5);
   BedroomPtr =
         LightScheduler_Create(LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY,
               MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightScheduler_Test_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest - 5;
   LightScheduler_Test_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightScheduler_Test_CheckEvent(&Expected, 2);
}

void test_LightSchedulerRandomize_TurnsOnOnlyOnceADayDecrementTime(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(10, -10);
   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest - 10 + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest + 10;
   LightScheduler_Test_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightScheduler_Test_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightScheduler_Test_CheckEvent(&Expected, 2);
}

void test_LightSchedulerRandomize_TurnsOnOnlyOnceADayIncrementTime(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(-10, 10);

   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 11);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightScheduler_Test_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightScheduler_Test_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest + 10;
   LightScheduler_Test_CheckEvent(&Expected, 2);
}

void test_LightSchedulerRandomize_RandomizeAtMidnight(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = (24 * 60 - 1);

   RandomMinute_Fake_SetFirstAndIncrement(-10, 10);
   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_THURSDAY, 10);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightScheduler_Test_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightScheduler_Test_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_THURSDAY;
   Expected.Time.Minute = 9;
   LightScheduler_Test_CheckEvent(&Expected, 2);
}

