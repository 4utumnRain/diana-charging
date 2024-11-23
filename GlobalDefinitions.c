/*
 * GlobalDefinitions.c
 *
 *  Created on: 12 Mar 2024
 *      Author: DELL
 */

#include "GlobalDefinitions.h"

_Bool Delay_100us(uint32_t Delay_time)
{
    static uint32_t delay_100us_count = 0;
    if( delay_100us_count < Delay_time){
        delay_100us_count++;
        return false;
    }
    else{
        delay_100us_count = 0;
        return true;
    }
}

_Bool Delay_100ms(uint32_t Delay_time)
{
    static uint32_t time_100us_count = 0;
    static uint32_t delay_100ms_count = 0;
    if( time_100us_count < 1000U) time_100us_count++;
    else {
        time_100us_count = 0;
        delay_100ms_count++;
    }

    if( delay_100ms_count < Delay_time)
        return false;
    else{
        delay_100ms_count = 0;
        return true;
    }
}

_Bool ISR_Delay_us(const uint32_t delayUS, const uint32_t SamplingTimeUS)
{
    static uint32_t delayCycleCnt = 0;
    const uint32_t endDelayCnt = (uint32_t)(delayUS/SamplingTimeUS) + 1;
    if (delayCycleCnt < endDelayCnt)
    {
        delayCycleCnt++;
        return 0;
    }
    else
    {
        delayCycleCnt = 0;
        return 1;
    }
}

_Bool Waiting(uint32_t Seconds){
    static int cnt = 0;
    const int STOPVALUE = Seconds/Tz;
    if (cnt>=STOPVALUE){
        cnt = 0;
        return true;
    }
    else cnt++;
    return false;
}
