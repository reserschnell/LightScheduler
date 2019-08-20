/*
 * RandomMinute_PBcfg.c
 *
 *  Created on: Dec 5, 2018
 *      Author: reser
 */


#include "RandomMinute_PBcfg.h"

#include "RandomMinute.h"

const RandomMinute_SpCalibType RandomMinute_SpCalib =
{
   .Bound =  RANDOMMINUTE_BOUND
};


const RandomMinute_ConfigType RandomMinute_Config =
{
   .SpCalib = &RandomMinute_SpCalib
};
