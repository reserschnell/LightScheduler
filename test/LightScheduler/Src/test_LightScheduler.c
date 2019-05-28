#include "unity.h"
#include "LightScheduler_PBcfg.h"
#include "LightScheduler.h"
#include "TimeService_Types.h"
#include "LightController.h"
#include "LightController_PBcfg.h"
#include "TimeService_Fake.h"
#include "RandomMinute_PBcfg.h"
#include "RandomMinute.h"

TEST_FILE("TimeService.c")
TEST_FILE("LightController_DriverSpy.c")

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
}

void tearDown(void)
{
}

void test_LightScheduler_NoChangesToLightDuringInitialization(void)
{
   CheckEvent(&Default, 0);
}

void test_LightScheduler_RememberTheLastLightIdControlled(void)
{
   LightController_On(LIGHTCONTROLLER_BATHROOM);

   Expected.Id = LIGHTCONTROLLER_BATHROOM;
   CheckEvent(&Expected, 0);
   CheckEvent(&Default, 1);
}

void test_LightScheduler_NoScheduleNotingHappens(void)
{
   TimeService_Fake_RunUntil(TIMESERVICE_MONDAY, 100);

   CheckEvent(&Default, 0);
}

void test_LightScheduler_ScheduleOnEveryNotTimeYet(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_EVERYDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_MONDAY, MinuteToTest);

   CheckEvent(&Default, 0);
}

void test_LightScheduler_ScheduleOnEverydayItsTime(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_EVERYDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   CheckEvent(&Expected, 1);

   CheckEvent(&Default, 2);
}

void test_LightScheduler_ScheduleOffEverydayItsTime(void)
{
   uint16 const MinuteToTest = 1200;
   LightSchedulerDataType * SchedulePtr;

   SchedulePtr = LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_EVERYDAY,
         MinuteToTest);
   LightScheduler_TurnOff(SchedulePtr);

   TimeService_Fake_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_OFF;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   CheckEvent(&Expected, 1);

   CheckEvent(&Default, 2);
}

void test_LightScheduler_ScheduleTuesdayButItsMonday(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_TUESDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest);

   CheckEvent(&Default, 0);
}

void test_LightScheduler_ScheduleTuesdayAndItsTuesday(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_TUESDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);
   CheckEvent(&Default, 1);
}

void test_LightScheduler_ScheduleWeekendAndItsWeekday(void)
{
   uint16 const MinuteToTest = 800;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEEKEND,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_SATURDAY, MinuteToTest);

   CheckEvent(&Default, 0);
}

void test_LightScheduler_ScheduleWeekendAndItsWeekend(void)
{
   uint16 const MinuteToTest = 300;

   LightScheduler_Create(
         LIGHTCONTROLLER_CHILD2,
         LIGHTSCHEDULER_WEEKEND,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_SUNDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_CHILD2;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_SATURDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_SUNDAY;
   CheckEvent(&Expected, 1);

   CheckEvent(&Default, 2);
}

void test_LightScheduler_ScheduleWeekdayAndItsWeekend(void)
{
   uint16 const MinuteToTest = 800;

   TimeService_Fake_SetStartTime(TIMESERVICE_FRIDAY, MinuteToTest);

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEEKDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_MONDAY, MinuteToTest);

   CheckEvent(&Default, 0);
}


void test_LightScheduler_ScheduleWeekdayAndItsWeekday(void)
{
   uint16 const MinuteToTest = 800;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEEKDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   CheckEvent(&Expected, 1);

   CheckEvent(&Default, 2);
}

void test_LightScheduler_ScheduleTwoEventsAtTheSameTime(void)
{
   uint16 const MinuteToTest = 800;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEDNESDAY,
         MinuteToTest);

   LightScheduler_Create(
         LIGHTCONTROLLER_BATHROOM,
         LIGHTSCHEDULER_WEDNESDAY,
         MinuteToTest);

   TimeService_Fake_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);

   Expected.Id = LIGHTCONTROLLER_BATHROOM;
   CheckEvent(&Expected, 1);

   CheckEvent(&Default, 2);
}

void test_LightScheduler_RejectTooManyEvents(void)
{
   int i;
   LightSchedulerDataType * ReturnPtr;

   for (i = 0; i < LIGHTSCHEDULER_MAX_EVENTS; i++)
   {
      ReturnPtr =
            LightScheduler_Create(
                  LIGHTCONTROLLER_BEDROOM,
                  LIGHTSCHEDULER_WEDNESDAY,
                  i);
      TEST_ASSERT_NOT_NULL(ReturnPtr);
   }
   ReturnPtr =
         LightScheduler_Create(
               LIGHTCONTROLLER_BEDROOM,
               LIGHTSCHEDULER_WEDNESDAY,
               i + 1);

   TEST_ASSERT_NULL(ReturnPtr);
}

void test_LightScheduler_RemoveRecyclesScheduledSlot(void)
{
   int i;
   LightSchedulerDataType * ReturnPtr;

   for (i = 0; i < LIGHTSCHEDULER_MAX_EVENTS; i++)
   {
      ReturnPtr =
            LightScheduler_Create(
                  LIGHTCONTROLLER_BEDROOM,
                  LIGHTSCHEDULER_WEDNESDAY,
                  i);
      TEST_ASSERT_NOT_NULL(ReturnPtr);
   }

   LightScheduler_Remove(ReturnPtr);

   ReturnPtr =
         LightScheduler_Create(
               LIGHTCONTROLLER_BEDROOM,
               LIGHTSCHEDULER_WEDNESDAY,
               800);

   TEST_ASSERT_NOT_NULL(ReturnPtr);
}

void test_LightScheduler_RemoveScheduleCantBeFound(void)
{
   LightSchedulerDataType * ReturnPtr;
   Std_ReturnType ReturnValue;

   ReturnPtr =
         LightScheduler_Create(
               LIGHTCONTROLLER_BEDROOM,
               LIGHTSCHEDULER_WEDNESDAY,
               800);

   ReturnValue =
         LightScheduler_Remove(ReturnPtr);
   TEST_ASSERT_EQUAL(E_OK, ReturnValue);

   ReturnValue =
         LightScheduler_Remove(ReturnPtr);
   TEST_ASSERT_EQUAL(E_NOT_OK, ReturnValue);
}

void test_LightScheduler_RemoveMultipleScheduledEvents(void)
{
   LightSchedulerDataType * BedroomPtr;
   uint16 const MinuteToTest = 800;

   BedroomPtr =
         LightScheduler_Create(
               LIGHTCONTROLLER_BEDROOM,
               LIGHTSCHEDULER_WEDNESDAY,
               MinuteToTest);

   LightScheduler_Create(
         LIGHTCONTROLLER_KITCHEN,
         LIGHTSCHEDULER_WEDNESDAY,
         MinuteToTest);

   LightScheduler_Remove(BedroomPtr);

   TimeService_Fake_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_KITCHEN;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   CheckEvent(&Expected, 0);

   CheckEvent(&Default, 1);
}

