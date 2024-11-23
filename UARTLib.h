/*
 * UARTLib.h
 *
 *  Created on: Nov 7, 2024
 *      Author: admin
 */

#ifndef UARTLIB_H_
#define UARTLIB_H_
#include "ti_msp_dl_config.h"
#include <string.h>
#include <stdio.h>
#include<stdlib.h>


void clearArray(char a[]);
void splitArray(const char a[], int *b, int *c);

#endif /* UARTLIB_H_ */
