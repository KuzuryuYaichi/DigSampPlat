/*
 * shared.c
 *
 *  Created on: 2020Äê7ÔÂ2ÈÕ
 *      Author: 27318
 */
#include "shared.h"

volatile struct CONFIG_POS_STRUCT (*ConfigPosStruct)[1] = SHARED_BASE_PTR;
