/*
 * RandomMinute.h
 *
 *  Created on: Dec 5, 2018
 *      Author: reser
 */

#ifndef RANDOMMINUTE_H_
#define RANDOMMINUTE_H_

#include "Std_Types.h"


typedef struct
{
   uint16 Bound;
}RandomMinuteConfigType;


extern void RandomMinute_Init(RandomMinuteConfigType const * const RandomMinuteConfig);



extern sint16 RandomMinute_Get(void);



#endif /* RANDOMMINUTE_H_ */
