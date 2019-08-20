/*
 * RandomMinute.c
 *
 *  Created on: Dec 5, 2018
 *      Author: reser
 */


#include "RandomMinute.h"
#include "stdlib.h"


typedef struct
{
   const RandomMinute_SpCalibType * SpCalib;
}RandomMinute_Type;


static RandomMinute_Type RandomMinute;

void RandomMinute_Init(const RandomMinute_ConfigType * const RandomMinute_Config)
{
   RandomMinute.SpCalib = RandomMinute_Config->SpCalib;
}



sint16 RandomMinute_Get(void)
{
   RandomMinute_SpCalibType const * SpCalib;
   sint16 Random;

   SpCalib = RandomMinute.SpCalib;

   Random = (sint16)((rand() >> 16)*((int)SpCalib->Bound * 2)/(RAND_MAX >> 16));
   Random = Random - (sint16)SpCalib->Bound;
   return (Random);

}
