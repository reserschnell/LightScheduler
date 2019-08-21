
#include "unity.h"
#include "LightController_PBcfg.h"
#include "LightController.h"
#include "LightController_DriverSpy.h"
#include "LightController_DriverCount.h"

#include "mock_TimeService_Os.h"

TEST_FILE("TimeService.c")


//#include "LightScheduler_Test.h"
//
//#include "LightScheduler_PBcfg.h"
//#include "LightScheduler.h"
//#include "RandomMinute_PBcfg.h"
//#include "RandomMinute.h"
//#include "TimeService_Os_Mock.h"

//
//
//TEST_FILE("LightController.c")



static LightController_DriverSpyEventType Default;



void setUp(void)
{
   LightController_Init(&LightController_Config);

   Default = LightController_DriverSpy_GetDefault();

   TimeService_Os_GetTime_ExpectAnyArgs();
   TimeService_Os_GetTime_ReturnThruPtr_Time(&(Default.Time));
}

void tearDown(void)
{
   LightController_DriverSpy_DeInit();
   LightController_DriverCount_DeInit();
}



void test_LightController_RememberTheLastLightIdControlled(void)
{

   LightController_On(LIGHTCONTROLLER_BATHROOM);

   Expected.LightControllerId = LIGHTCONTROLLER_BATHROOM;
   LightController_DriverSpy_CheckEvent(&Expected, 0);
}


void test_LightController_TurnOnDifferentDriverTypes(void)
{

   LightController_SetDriver(LIGHTCONTROLLER_KITCHEN, &LightController_DriverCount_Config);

   LightController_On(LIGHTCONTROLLER_KITCHEN);
   LightController_Off(LIGHTCONTROLLER_KITCHEN);

   LightController_On(LIGHTCONTROLLER_LIVINGROOM);


   TEST_ASSERT_EQUAL_UINT16(2, LightController_DriverCount_GetEventCntr());

   Expected.LightControllerId = LIGHTCONTROLLER_LIVINGROOM;
   LightController_DriverSpy_CheckEvent(&Expected, 0);
}

