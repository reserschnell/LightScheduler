
#include "unity.h"
#include "LightScheduler_Test.h"

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




void setUp(void)
{
   LightScheduler_Test_SetUp();
}

void tearDown(void)
{
   LightController_DriverSpy_CheckDefault();
}

void test_LightScheduler_NoChangesToLightDuringInitialization(void)
{
   //Implicitly checked in tearDown
}

void test_LightScheduler_NoScheduleNotingHappens(void)
{
   LightScheduler_Test_RunUntil(TIMESERVICE_MONDAY, 100);
}

void test_LightScheduler_ScheduleOnEveryNotTimeYet(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_EVERYDAY,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_MONDAY, MinuteToTest);
}

void test_LightScheduler_ScheduleOnEverydayItsTime(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_EVERYDAY,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   LightController_DriverSpy_CheckEvent(&Expected, 1);
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

   LightScheduler_Test_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_OFF;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   LightController_DriverSpy_CheckEvent(&Expected, 1);
}

void test_LightScheduler_ScheduleTuesdayButItsMonday(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_TUESDAY,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest);
}

void test_LightScheduler_ScheduleTuesdayAndItsTuesday(void)
{
   uint16 const MinuteToTest = 1200;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_TUESDAY,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_TUESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);
}

void test_LightScheduler_ScheduleWeekendAndItsWeekday(void)
{
   uint16 const MinuteToTest = 800;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEEKEND,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_SATURDAY, MinuteToTest);
}

void test_LightScheduler_ScheduleWeekendAndItsWeekend(void)
{
   uint16 const MinuteToTest = 300;

   LightScheduler_Create(
         LIGHTCONTROLLER_CHILD2,
         LIGHTSCHEDULER_WEEKEND,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_SUNDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_CHILD2;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_SATURDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_SUNDAY;
   LightController_DriverSpy_CheckEvent(&Expected, 1);
}

void test_LightScheduler_ScheduleWeekdayAndItsWeekend(void)
{
   uint16 const MinuteToTest = 800;

   TimeService_Os_Mock_SetTime(TIMESERVICE_FRIDAY, MinuteToTest);

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEEKDAY,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_MONDAY, MinuteToTest);
}


void test_LightScheduler_ScheduleWeekdayAndItsWeekday(void)
{
   uint16 const MinuteToTest = 800;

   LightScheduler_Create(
         LIGHTCONTROLLER_BEDROOM,
         LIGHTSCHEDULER_WEEKDAY,
         MinuteToTest);

   LightScheduler_Test_RunUntil(TIMESERVICE_TUESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.Time.Day = TIMESERVICE_MONDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Time.Day = TIMESERVICE_TUESDAY;
   LightController_DriverSpy_CheckEvent(&Expected, 1);
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

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_BEDROOM;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);

   Expected.Id = LIGHTCONTROLLER_BATHROOM;
   LightController_DriverSpy_CheckEvent(&Expected, 1);
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

   LightScheduler_Test_RunUntil(TIMESERVICE_WEDNESDAY, MinuteToTest + 1);

   Expected.Id = LIGHTCONTROLLER_KITCHEN;
   Expected.State = LIGHTCONTROLLER_STATE_ON;
   Expected.Time.Day = TIMESERVICE_WEDNESDAY;
   Expected.Time.Minute = MinuteToTest;
   LightController_DriverSpy_CheckEvent(&Expected, 0);
}

