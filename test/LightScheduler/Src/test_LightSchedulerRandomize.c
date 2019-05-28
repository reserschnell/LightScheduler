#include "unity.h"
#include "LightScheduler_PBcfg.h"
#include "LightScheduler.h"
#include "TimeService_Types.h"
#include "TimeService_Fake.h"
#include "RandomMinute_PBcfg.h"
#include "RandomMinute.h"
#include "RandomMinute_Fake.h"
#include "LightController_DriverSpy.h"
#include "LightController_PBcfg.h"

TEST_FILE("TimeService.c")
TEST_FILE("LightController_DriverSpy.c")
TEST_FILE("LightController.c")

static LightController_DriverSpyEventType Expected;

static LightController_DriverSpyEventType const Default =
{
   LIGHTCONTROLLER_ID_UNKNOWN,
   LIGHTCONTROLLER_STATE_ON,
   {
      TIMESERVICE_MONDAY,
      0
   }
};

LightSchedulerMConfigType const LightScheduler_FakeMConfig =
{
      RandomMinute_Fake_Get
};

LightSchedulerConfigType const LightScheduler_FakeConfig =
{
      &LightScheduler_FakeMConfig
};


#define NumberOfEvents 10
static TimeService_Time StartTime;
static TimeService_Time StopTime;
static TimeService_Time EventTime[NumberOfEvents];
static TimeService_Time ExpectedEventTime[NumberOfEvents];


static void CheckEvent(LightController_DriverSpyEventType const * const ExpectedEvent, uint16 NumberGivenEvent)
{
   LightController_DriverSpyEventType Given;
   Given = LightController_DriverSpy_GetEvent(NumberGivenEvent);

   TEST_ASSERT_EQUAL(ExpectedEvent->Id, Given.Id);
   TEST_ASSERT_EQUAL(ExpectedEvent->State, Given.State);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Day, Given.Time.Day);
   TEST_ASSERT_EQUAL(ExpectedEvent->Time.Minute, Given.Time.Minute);
}

static void SetTime(TimeService_DayType Day, uint16 Minute)
{
   TimeService_Fake_SetDay(Day);
   TimeService_Fake_SetMinute(Minute);
}


void setUp(void)
{
   int i;

   TimeService_Fake_Init();
   LightController_Init(&LightController_Config);
   LightScheduler_Init(&LightSchedulerConfig);
   RandomMinute_Init(&RandomMinuteConfig);
   StartTime.Day = TIMESERVICE_MONDAY;
   StartTime.Minute = 0;
   StopTime = StartTime;

   for (i = 0; i < NumberOfEvents; i++)
   {
      EventTime[i] = StartTime;
      ExpectedEventTime[i] = StartTime;
   }

   Expected = Default;

   LightScheduler_Init(&LightScheduler_FakeConfig);
}

void tearDown(void)
{
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

   TimeService_Fake_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest - 5;
   CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 2);

   CheckEvent(&Default, 3);
}

void test_LightSchedulerRandomize_TurnsOnOnlyOnceADayDecrementTime(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(10, -10);
   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   TimeService_Fake_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest - 10 + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest + 10;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   CheckEvent(&Expected, 2);

   CheckEvent(&Default, 3);
}

void test_LightSchedulerRandomize_TurnsOnOnlyOnceADayIncrementTime(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = 600;

   RandomMinute_Fake_SetFirstAndIncrement(-10, 10);

   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   TimeService_Fake_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 11);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest + 10;
   CheckEvent(&Expected, 2);

   CheckEvent(&Default, 3);
}

void test_LightSchedulerRandomize_RandomizeAtMidnight(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = (24 * 60 - 1);

   RandomMinute_Fake_SetFirstAndIncrement(-10, 10);
   BedroomPtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM, LIGHTSCHEDULER_EVERYDAY, MinuteToTest);
   LightScheduler_Randomize(BedroomPtr);

   TimeService_Fake_RunUntil(TIMESERVICE_THURSDAY, 10);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest - 10;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 1);

   Expected.Time.Day = TIMESERVICE_THURSDAY;
   Expected.Time.Minute = 9;
   CheckEvent(&Expected, 2);

   CheckEvent(&Default, 3);
}

