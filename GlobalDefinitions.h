/*
 * GlobalDefinitions.h
 *
 *  Created on: 12 Mar 2024
 *      Author: DELL
 */

#ifndef GLOBALDEFINITIONS_H_
#define GLOBALDEFINITIONS_H_

#include "ti_msp_dl_config.h"

typedef enum{
    /*--------------Normal Operating Modes---------------*/
    MODE_IDLE              = 0x00,
    MODE_BATTERY_CHECK     = 0x01,
    MODE_CHARGING_REQUEST  = 0x02,
    MODE_SOFT_START        = 0x03,
    MODE_HAND_SHAKE        = 0x04,
    MODE_PRECHARGE         = 0x05,
    MODE_BULK_CHARGE       = 0x06,
    MODE_FULLY_CHARGED     = 0x07,
    MODE_OPEN_LOOP         = 0x08,
    MODE_CLOSE_LOOP        = 0x09,


    /*--------------------Operating Protection Modes--------------------*/
    MODE_OCP1              = 0xB0,
    MODE_OCP2              = 0xB1,
    MODE_OVP               = 0xB2,
    MODE_OTP               = 0xB3,
    MODE_OT                = 0xB4,
    MODE_IVP               = 0xB5,
    MODE_OFP               = 0xB6,
    MODE_CHARGING          = 0xB7,
    MODE_READ_MEMORY       = 0x0C,

    ERR_HARDWARE           = 0xE0,
    ERR_PRECHARGE_TIMEOUT  = 0xE1,
    ERR_CHARGE_TIMEOUT     = 0xE2
} Operating_Mode;

typedef enum{
    PRECHARGE       = 0x00,
    BULKCHARGE      = 0x01,
    FULL            = 0x02,
    FLOATCHARGE     = 0x03,
} ChargingStage;


typedef struct{
    uint32_t vref;
    uint32_t irefmin;
    uint32_t irefmax;
    uint32_t Fxmin;
    uint32_t Fxmax;
    uint32_t Dmin;
    uint32_t Dmax;
    uint16_t Status;
} ControllerParams;

typedef struct{
    float vref;
    float irefmin;
    float irefmax;
    float Fxmin;
    float Fxmax;
    float Dmin;
    float Dmax;
    float Status;
} ControllerParams_NotIQMath;

typedef struct{
    uint32_t vref;
    uint32_t irefmin;
    uint32_t irefmax;
    uint32_t Fmin;
    uint32_t Fmax;
    uint32_t Dmin;
    uint32_t Dmax;
    uint16_t Status;
} ControllerParams_mod_Q;

typedef struct{
    uint32_t voltage;
    uint32_t current;
    uint32_t time;
    uint16_t status;
} ChargingProfileParams;

typedef struct{
    float Vref;
    float Irefmin;
    float Irefmax;
    float CtrlVarmin;
    float CtrlVarmax;
    float Tsp;
    uint16_t Status;
} ControllerParams_LLC;


#define PI                  3.141592654f
#define Q                   14U
#define Q_Hai               9U
#define Q_diff              5U

/*---------Initial params-----------*/
#define Tz                  50e-6f

/*---------Temperature profile params-----------*/
#define LOWTEMP     75U
#define HIGHTEMP    85U
#define TEMPINIT    70U
#define TEMPMAX     85U

/*---------Charging Profile params-----------*/
#define VMAX        50.0f
#define VBULK       42.0f
#define VFLOAT      40.0f
#define VDDCHRG     25.0f
#define VLOW        20.0f
#define VMIN        20.0f
#define VLOWEST     20.0f

#define IMAX        10.0f
#define IBULK       5.0f
#define IPRE        1.0f
#define IMIN        1.0f

//#define VMAX        75.0f
//#define VBULK       73.0f
//#define VFLOAT      65.0f
//#define VDDCHRG     54.0f
//#define VLOW        36.0f
//#define VMIN        34.0f
//#define VLOWEST     5.0f
//
//#define IMAX        6.5f
//#define IBULK       3.0f
//#define IPRE        0.5f
//#define IMIN        0.5f

#define MAXIMUM_PROTECTION_RESET_TIMES  3U
//#define VMAX        37.0f
//#define VBULK       35.0f
//#define VFLOAT      33.0f
//#define VDDCHRG     29.0f
//#define VLOW        16.0f
//#define VMIN        15.0f
//
//#define IMAX        4.0f
//#define IBULK       2.0f
//#define IPRE        1.0f
//#define IMIN        0.3f

/*---------Soft Start Params-----------*/
/*---------Anti windup parameters-----------*/
#define RESONANT_FREQ       150e3
#define FxMIN   0.66f
#define FxMAX   3.33f
#define DMIN    0.15f
#define DMAX    0.50f

#define FMIN    100000.0f
#define FMAX    500000.0f

/*--------- Measurement circuits params-----------*/
#define VO_GAIN      0.0304f
#define VBAT_GAIN    0.0274f
#define IBAT_GAIN    0.0135f

//#define TRANSIENTTIME 1

#define TEMPERATURE_SAMPLING_CYCLE      (uint32_t)(250000) //5s

#define MAX_RESET_TIMES     3U  /* System reset times after error */

#define OTP_TIMEOUT         50000U //Cycles
#define OVP_TIMEOUT         10U  //Cycles
#define FLL_CHRG_TIMEOUT    50000U //Cycles = 50000*20e-6 = 1s

#define UARTbuffersize 100U
uint16_t ADCbuffer[4];
int mcuVac;
int mcuTemp;
char txUART[UARTbuffersize];
char rxUART[1];
int flag1;
Operating_Mode Mode;
static bool onetime_integral_frequency = false;

void System_Delay(uint16_t delay_time_ms);
_Bool Delay_100us(uint32_t Delay_time);
_Bool Delay_100ms(uint32_t Delay_time);
_Bool ISR_Delay_us(const uint32_t delayUS, const uint32_t SamplingTimeUS);
_Bool Waiting(uint32_t Seconds);

#endif /* GLOBALDEFINITIONS_H_ */
