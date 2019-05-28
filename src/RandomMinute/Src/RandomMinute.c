/*
 * RandomMinute.c
 *
 *  Created on: Dec 5, 2018
 *      Author: reser
 */


#include "RandomMinute.h"
#include "stdlib.h"


typedef struct RandomMinuteType_Tag
{
   RandomMinuteConfigType const * CfgPtr;
}RandomMinuteType;


RandomMinuteType RandomMinute;

void RandomMinute_Init(RandomMinuteConfigType const * const RandomMinuteConfig)
{
   RandomMinute.CfgPtr = RandomMinuteConfig;
}



sint16 RandomMinute_Get(void)
{
   RandomMinuteConfigType const * CfgPtr;
   sint16 Random;

   CfgPtr = RandomMinute.CfgPtr;

   Random = (sint16)((rand() >> 16)*((int)CfgPtr->Bound * 2)/(RAND_MAX >> 16));
   Random = Random - (sint16)CfgPtr->Bound;
   return (Random);

}
