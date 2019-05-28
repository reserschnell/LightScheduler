/*
 * LightSchedulerPBcfg.c
 *
 *  Created on: Dec 11, 2018
 *      Author: reser
 */


#include "LightScheduler_PBcfg.h"


#include "RandomMinute.h"

LightSchedulerMConfigType const LightSchedulerMConfig =
{
   RandomMinute_Get
};

LightSchedulerConfigType const LightSchedulerConfig =
{
   &LightSchedulerMConfig
};

