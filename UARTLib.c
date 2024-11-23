/*
 * UARTLib.c
 *
 *  Created on: Nov 7, 2024
 *      Author: admin
 */

#include "UARTLib.h"



void clearArray(char a[])
{
    int length = strlen(a);
    for (int j = 0; j < length; j++)
    {
        a[j] = '\0';
    }
}
void splitArray(const char a[], int *b, int *c) {
    char b1[10];   //Array first number
    char c1[10] ;  // Second first number
    int i = 0, j = 0;

    while (a[i] != ' ' && a[i] != '\0') {
        b1[i] = a[i];
        i++;
    }
    b1[i] = '\0';  // End b1

    if (a[i] == ' ') {
        i++;
    }

    while (a[i] != '\0') {
        c1[j] = a[i];
        i++;
        j++;
    }
    c1[j] = '\0';  // End c1

    // Convert to int
    *b = atoi(b1);
    *c = atoi(c1);
}

