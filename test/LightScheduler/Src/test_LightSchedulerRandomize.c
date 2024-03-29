
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
#include "LightController_DriverCount.h"


TEST_FILE("LightController.c")
TEST_FILE("TimeService.c")


LightScheduler_SpConstType const LightScheduler_FakeMConfig =
{
      RandomMinute_Fake_Get
};

LightScheduler_ConfigType const LightScheduler_FakeConfig =
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
   LightController_DriverSpy_CheckDefault();

   LightController_DriverSpy_DeInit();
   LightController_DriverCount_DeInit();
}


void test_LightSchedulerRandomize_TurnsOnEarly(void)
{
   LightScheduler_SelfType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(-10, 5);
   BedroomPtr =
         LightScheduler_Create(LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY,
               MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.LightControllerId = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest - 5;
   LightController_DriverSpy_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 2);
}

void test_LightSchedulerRandomize_TurnsOnOnlyOnceADayDecrementTime(void)
{
   LightScheduler_SelfType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(10, -10);
   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest - 10 + 1);

   Expected.LightControllerId = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest + 10;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightController_DriverSpy_CheckEvent(&Expected, 2);
}

void test_LightSchedulerRandomize_TurnsOnOnlyOnceADayIncrementTime(void)
{
   LightScheduler_SelfType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(-10, 10);

   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 11);

   Expected.LightControllerId = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest + 10;
   LightController_DriverSpy_CheckEvent(&Expected, 2);
}

void test_LightSchedulerRandomize_RandomizeAtMidnight(void)
{
   LightScheduler_SelfType * BedroomPtr;
   uint16 const MinuteToTest = (24 * 60 - 1);

   RandomMinute_Fake_SetFirstAndIncrement(-10, 10);
   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   LightScheduler_Test_RunUntil(TIMESERVICE_THURSDAY, 10);

   Expected.LightControllerId = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_THURSDAY;
   Expected.Time.Minute = 9;
   LightController_DriverSpy_CheckEvent(&Expected, 2);
}

