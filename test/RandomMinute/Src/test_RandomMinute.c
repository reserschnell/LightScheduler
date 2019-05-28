
//#include "gtest/gtest.h"
//
//extern "C"
//{
//#include "Std_Types.h"
//#include "RandomMinute_Test.h"
//#include "RandomMinute.h"
//#include "RandomMinute_PBcfg.h"
//#include "stdlib.h"
//#include "stdio.h"
//}
//
//namespace
//{
//
//   class RandomMinute: public testing::Test
//   {
//   public:
//
//   protected:
//
//      // Remember that SetUp() is run immediately before a test starts.
//      // This is a good place to record the start time.
//      virtual void SetUp()
//      {
//         RandomMinute_Init(&RandomMinuteConfig);
//         srand(1);
//      }
//
//      // TearDown() is invoked immediately after a test finishes.  Here we
//      // check if the test was too slow.
//      virtual void TearDown()
//      {
//
//      }
//
//      void AssertMinuteIsInRange(sint16 Minute)
//      {
//         if (!(-(sint16)RandomMinuteConfig.Bound <= Minute
//               && Minute <= (sint16)RandomMinuteConfig.Bound))
//         {
//            printf("Test");
//         }
//         EXPECT_TRUE((-(sint16)RandomMinuteConfig.Bound <= Minute
//               && Minute <= (sint16)RandomMinuteConfig.Bound));
//      }
//
//   };
//
////END: monitorLoop
//
//   TEST_F(RandomMinute, GetIsInRange)
//   {
//      sint16 Minute;
//      for (int i = 0; i < 100; i++)
//      {
//         Minute = RandomMinute_Get();
//         AssertMinuteIsInRange(Minute);
//
//      }
//   }
//
//   TEST_F(RandomMinute, AllValuesPossible)
//   {
//      sint16 Minute;
//      const sint16 SizeOfErrorCntr = (sint16)(RandomMinuteConfig.Bound*2 +1);
//      sint16 ErrorCntr = 0;
//      sint16 ResultCntr[RandomMinuteConfig.Bound*2 +1] = {0};
//      sint16 i;
//
//      for (i = 0; i < 300; i++)
//      {
//         Minute = RandomMinute_Get();
//         AssertMinuteIsInRange(Minute);
//         ResultCntr[Minute + (sint16)RandomMinuteConfig.Bound]++;
//      }
//      for (i = 0; i < SizeOfErrorCntr; i++)
//      {
//         if (ResultCntr[i] == 0)
//         {
//            ErrorCntr++;
//         }
//      }
//      EXPECT_EQ(ErrorCntr, 0);
//   }
//
//}// namespace
