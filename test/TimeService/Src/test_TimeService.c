
//#include "gtest/gtest.h"
//
//extern "C"
//{
//#include "Std_Types.h"
//#include "TimeService_Test.h"
//#include "TimeService.h"
//#include "TimeService_Fake.h"
//}
//
//namespace
//{
//
//   class TimeService: public testing::Test
//   {
//   public:
//
//   protected:
//
//      uint16 const MinutesPerDay = 24*60;
//
//      // Remember that SetUp() is run immediately before a test starts.
//      // This is a good place to record the start time.
//      virtual void SetUp()
//      {
//
//      }
//
//      // TearDown() is invoked immediately after a test finishes.  Here we
//      // check if the test was too slow.
//      virtual void TearDown()
//      {
//
//      }
//
//      void SetTime(TimeService_DayType Day, uint16 Minute)
//      {
//         TimeService_Fake_SetDay(Day);
//         TimeService_Fake_SetMinute(Minute);
//      }
//
//   };
//
////END: monitorLoop
//
//   TEST_F(TimeService, TimeService_Add_Monday2TuesdayByMinute)
//   {
//      TimeService_Time TimeNow;
//      uint16 const MinuteNow = MinutesPerDay-1;
//
//      TimeNow.Day = TIMESERVICE_MONDAY;
//      TimeNow.Minute = MinuteNow;
//
//      TimeService_Add(&TimeNow, 0, 1);
//
//      EXPECT_EQ(TimeNow.Day, TIMESERVICE_TUESDAY);
//      EXPECT_EQ(TimeNow.Minute, 0);
//
//   }
//
//
//   TEST_F(TimeService, TimeService_Add_Monday2TuesdayByDay)
//   {
//      TimeService_Time TimeNow;
//      uint16 const MinuteNow = MinutesPerDay-1;
//
//      TimeNow.Day = TIMESERVICE_MONDAY;
//      TimeNow.Minute = MinuteNow;
//
//      TimeService_Add(&TimeNow, 1, 0);
//
//      EXPECT_EQ(TIMESERVICE_TUESDAY, TimeNow.Day);
//      EXPECT_EQ(TimeNow.Minute, MinuteNow);
//
//   }
//
//
//   TEST_F(TimeService, TimeService_Add_Monday2SundayByMinute)
//   {
//      TimeService_Time TimeNow;
//      uint16 const MinuteNow = MinutesPerDay-1;
//
//      TimeNow.Day = TIMESERVICE_MONDAY;
//      TimeNow.Minute = MinuteNow;
//
//      TimeService_Add(&TimeNow, 0, -(sint16)MinutesPerDay);
//
//      EXPECT_EQ(TIMESERVICE_SUNDAY, TimeNow.Day);
//      EXPECT_EQ(TimeNow.Minute, MinuteNow);
//
//   }
//
//
//   TEST_F(TimeService, TimeService_Add_Monday2SundayByDay)
//   {
//      TimeService_Time TimeNow;
//      uint16 const MinuteNow = MinutesPerDay-1;
//
//      TimeNow.Day = TIMESERVICE_MONDAY;
//      TimeNow.Minute = MinuteNow;
//
//      TimeService_Add(&TimeNow, -1, 0);
//
//      EXPECT_EQ(TIMESERVICE_SUNDAY, TimeNow.Day);
//      EXPECT_EQ(TimeNow.Minute, MinuteNow);
//
//   }
//
//
//   TEST_F(TimeService, TimeService_Add_Monday2WednesdayByDayAndMinute)
//   {
//      TimeService_Time TimeNow;
//      uint16 const MinuteNow = MinutesPerDay-1;
//
//      TimeNow.Day = TIMESERVICE_MONDAY;
//      TimeNow.Minute = MinuteNow;
//
//      TimeService_Add(&TimeNow, 8, (sint16)MinutesPerDay);
//
//      EXPECT_EQ(TIMESERVICE_WEDNESDAY, TimeNow.Day);
//      EXPECT_EQ(TimeNow.Minute, MinuteNow);
//
//   }
//
//
//   TEST_F(TimeService, TimeService_Add_Monday2SaturdayByDayAndMinute)
//   {
//      TimeService_Time TimeNow;
//      uint16 const MinuteNow = MinutesPerDay-1;
//
//      TimeNow.Day = TIMESERVICE_MONDAY;
//      TimeNow.Minute = MinuteNow;
//
//      TimeService_Add(&TimeNow, -8, -(sint16)MinutesPerDay);
//
//      EXPECT_EQ(TIMESERVICE_SATURDAY, TimeNow.Day);
//      EXPECT_EQ(TimeNow.Minute, MinuteNow);
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsNowEqualTo)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = MinutesPerDay-1;
//
//      SetTime(TIMESERVICE_MONDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_MONDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowEqualTo(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsLaterThenNowSameDay)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = MinutesPerDay-1;
//
//      SetTime(TIMESERVICE_TUESDAY, TestMinute-1);
//
//      TestTime.Day = TIMESERVICE_TUESDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsLaterThenNowNextDay)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = MinutesPerDay-1;
//
//      SetTime(TIMESERVICE_TUESDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_WEDNESDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsLaterThenNowPlus3Days)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = MinutesPerDay-1;
//
//      SetTime(TIMESERVICE_TUESDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_FRIDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsLaterThenNowMinus4Days)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = MinutesPerDay-1;
//
//      SetTime(TIMESERVICE_SATURDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_TUESDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowEarlierThen(&TestTime));
//   }
//
//
//   TEST_F(TimeService, TimeService_IsEarlierThenNowSameDay)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = 0;
//
//      SetTime(TIMESERVICE_TUESDAY, TestMinute+1);
//
//      TestTime.Day = TIMESERVICE_TUESDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowLaterThen(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsEarlierThenNowPreviousDay)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = 0;
//
//      SetTime(TIMESERVICE_WEDNESDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_TUESDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowLaterThen(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsEarlierThenNowMinus3Days)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = 0;
//
//      SetTime(TIMESERVICE_FRIDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_TUESDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowLaterThen(&TestTime));
//
//   }
//
//
//   TEST_F(TimeService, TimeService_IsEarlierThenNowPlus4Days)
//   {
//      TimeService_Time TestTime;
//      uint16 const TestMinute = 0;
//
//      SetTime(TIMESERVICE_TUESDAY, TestMinute);
//
//      TestTime.Day = TIMESERVICE_SATURDAY;
//      TestTime.Minute = TestMinute;
//
//      EXPECT_TRUE(TimeService_IsNowLaterThen(&TestTime));
//   }
//
//}// namespace
