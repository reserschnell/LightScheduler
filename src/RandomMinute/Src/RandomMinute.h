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
   const uint16 Bound;
}RandomMinute_SpCalibType;


typedef struct
{
   const RandomMinute_SpCalibType * SpCalib;
}RandomMinute_ConfigType;


extern void RandomMinute_Init(const RandomMinute_ConfigType * const RandomMinute_Config);



extern sint16 RandomMinute_Get(void);



#endif /* RANDOMMINUTE_H_ */
