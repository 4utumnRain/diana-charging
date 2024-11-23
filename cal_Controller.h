/*
 * Controller.h
 *
 *  Created on: 12 Mar 2024
 *      Author: DELL
 */

#ifndef CAL_CONTROLLER_H_
#define CAL_CONTROLLER_H_

#include "ti_msp_dl_config.h"
#include "GlobalDefinitions.h"
#include <cal_FixedPointMath.h>

/* Define Quasi-Resonant parameters */
#define woz     (float)628.3185307f
#define wop     (float)628.3185307f
#define Qoz     (float)1.0f
#define Qop     (float)30.0f
#define QN      12

extern const float b1;
extern const float b2;
extern const float a1;
extern const float a2;

/* Constant values in QR BW Digitalization */

extern const float w;
extern const float w1;
extern const float w2;

extern const float v;
extern const float v1;
extern const float v2;

extern const float v_d_w;
extern const float v1_d_w;
extern const float v2_d_w;
extern const float w1_d_w;
extern const float w2_d_w;

extern const int f_v_d_w_q12;
extern const int f_v1_d_w_q12;
extern const int f_v2_d_w_q12;
extern const int f_w1_d_w_q12;
extern const int f_w2_d_w_q12;



uint32_t    CTRL_getVIDualLoopControlledFx(int vbat_q15, int ibat_q15, ControllerParams CTRL_Params);
uint32_t    _CTRL_getFxDfromVIDualLoopController(int vbat_q15, int ibat_q15, ControllerParams CTRL_Params);
uint32_t    _CTRL_getFxDfromVIDualLoopControllerWith100HzCalcelation(int vbat_q9, int ibat_q9, ControllerParams_mod_Q CTRL_Params);
void        _CTRL_Reset_Dual_Controller();
void        _CTRL_Lookup_Adaptive_Controller_Parameters_Table(int vbat_q15, int *KPI_q15, int *KII_q15);
uint32_t    _CTRL_Get_PI_Controller(int e, int *integral, int KP, int KI, int highlimit, int lowlimit);
uint32_t    _CTRL_Get_PI_V_Controller_modified_Q(int e, int *integral, int KP, int KI, int highlimit, int lowlimit);
uint32_t    _CTRL_Get_PI_Controller_modified_Q(int e, int *integral, int KP, int KI, int highlimit, int lowlimit);
void        _CTRL_Get_Ramp_Up_Value(int input, int step, int *output);
uint32_t    _CTRL_getFxDfromIController_NoIQMath(float ibat, float iref);
uint32_t    _CTRL_getFxDfromDualVIController_NoIQMath(float vbat, float ibat);
uint32_t    _CTRL_Get_PI_IController_NoIQMath(float e, float *integral, float KP, float KI, float highlimit, float lowlimit);

#endif /* CAL_CONTROLLER_H_ */
