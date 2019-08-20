/*
 * LightSchedulerPBcfg.c
 *
 *  Created on: Dec 11, 2018
 *      Author: reser
 */


#include "LightScheduler_PBcfg.h"


#include "RandomMinute.h"

const LightScheduler_SpConstType LightScheduler_SpConst =
{
   RandomMinute_Get
};

const LightScheduler_ConfigType LightScheduler_Config =
{
   &LightScheduler_SpConst
};

