/*
 * Charger_Controller.h
 *
 *  Created on: 15 Nov 2023
 *      Author: DELL
 */

#ifndef APP_EBIKECHARGER_H_
#define APP_EBIKECHARGER_H_

#include <cal_Controller.h>
#include <cal_FixedPointMath.h>
#include <cal_Profile.h>
#include <drv_BotLayer.h>
#include "ti_msp_dl_config.h"
#include "GlobalDefinitions.h"


Operating_Mode Charger_State;
int WatchDog_Time;
int Global_Time;
int Over_Time_Threshold;
int Charge_Time_10ms;

//#define OPEN_LOOP_TEST

#define UPDATE_LED_TIME 40000

#define _IS_IVP()   (!(DL_GPIO_readPins(INPUT_SIGNALs_PORT, INPUT_SIGNALs_VIN_DETECTION_PIN)))
#define _IS_OVP()   ((vbat_ADC > VMAX_ADC))//(vo_ADC>VMAX_ADC)||
#define _IS_OCP1()  (_IS_OCP())
#define _IS_OCP2()  (ibat_ADC > IMAX_ADC)
#define _IS_OTP()   (temp_ADC > TEMPMAX_ADC)
#define _IS_NOTP()  (temp_ADC < TEMPINIT_ADC)
#define _IS_OFP()   IS_OFP
#define _IS_PROTECTING()    (Charger_State == MODE_OVP || Charger_State == MODE_OCP1 || Charger_State == MODE_OCP2 || Charger_State == MODE_OTP)

#define _IS_OPEN_LOOP()          (Charger_State == MODE_OPEN_LOOP)
#define _IS_CLOSE_LOOP()         (Charger_State == MODE_CLOSE_LOOP)
#define _IS_BATTERY_CHECK()      (!_IS_PROTECTING() && !(Charger_State == MODE_SOFT_START) && !(Charger_State==MODE_HAND_SHAKE) && vbat_ADC<VMIN_ADC)
#define _IS_CHARGING_REQUEST()   ((Charger_State == MODE_BATTERY_CHECK || Charger_State == MODE_FULLY_CHARGED) && (vbat_ADC > VLOW_ADC && vbat_ADC < VFLOAT_ADC) && WatchDog_Time > (TRANSIENT_TIME << 1U))
#define _IS_SOFT_START()         ((Charger_State == MODE_CHARGING_REQUEST && WatchDog_Time > (TRANSIENT_TIME << 1)) && temp_ADC <= TEMPMAX_ADC)
#define _IS_HAND_SHAKE()         (Charger_State == MODE_SOFT_START && vo_ADC >= vbat_ADC)
#define _IS_PRECHARGING()        (Charger_State == MODE_HAND_SHAKE && _LLC_RELAY_STT() && WatchDog_Time > TRANSIENT_TIME)
#define _IS_BULK_CHARGING()      (Charger_State == MODE_HAND_SHAKE && _LLC_RELAY_STT() && WatchDog_Time > TRANSIENT_TIME) //(Charger_State == MODE_PRECHARGE && vbat_ADC > VDDCHRG_ADC)
#define _IS_FULLY_CHARGED()      (Charger_State == MODE_BULK_CHARGE && vbat_ADC >= VBULK_ADC && ibat_ADC < IPRE_ADC)
#define _IS_CHARGING()           (Charger_State == MODE_PRECHARGE || Charger_State == MODE_BULK_CHARGE)

void    _CHRGR_Manage_Charger_Operations_State(uint16_t vbatADC, uint16_t voADC, uint16_t ibatADC, uint16_t tempADC);
void    _CHRGR_Manage_Protection_State(Operating_Mode *State, uint16_t vbat_ADC, uint16_t vo_ADC, uint16_t ibat_ADC, uint16_t temp_ADC);
void    _CHRGR_Manage_Charger_Operation_State(Operating_Mode *State, uint16_t vbat_ADC, uint16_t vo_ADC, uint16_t ibat_ADC, uint16_t temp_ADC);
void    _CHRGR_Execute_Battery_Check_State();
void    _CHRGR_Execute_Soft_Start_State(void);
void    _CHRGR_Execute_HandShake_State(void);
void    _CHRGR_Execute_Charging_State(uint16_t vbatADC, uint16_t voADC, uint16_t ibatADC, uint16_t tempADC);
void    _CHRGR_Execute_Charging_State_with_Modified_Q(uint16_t vbatADC, uint16_t voADC, uint16_t ibatADC, uint16_t tempADC);
void    _CHRGR_Execute_System_Stop(void);
void    _CHRGR_Execute_Open_Loop(uint16_t Fsw, uint16_t Duty, uint16_t Fixed_Deadtime);
void    _CHRGR_Execute_Close_Loop(uint16_t vbat_ADC, uint16_t ibat_ADC);
void    _CHRGR_Set_LED_Indicator(uint16_t vo_ADC);
char*   _CHRGR_Get_Charger_State(Operating_Mode Charging_Mode);
void    _CHRGR_Set_Over_Time_Threshold(int stopTime);
void    _CHRGR_Reset_Charger(void);
void    _CHRGR_Lastest_Err_LED_Indicator(Operating_Mode readChargerState);
bool    _Is_OTP(uint16_t tempAdc);
bool    _Is_OVP(uint16_t vbatAdc);
bool    _Is_Fully_Charged(uint16_t vbatAdc, uint16_t ibatAdc);
void    _CHRGR_Execute_Charging_State_CurrentLoop(uint16_t vbatADC, uint16_t voADC, uint16_t ibatADC, uint16_t tempADC);
void    _CHRGR_Execute_Charging_State_CurrentLoop_NotIQMath(float vbat, float vo, float ibat);

/*-------------------------- My definitions --------------------------------*/
#define SamplingTime    50e-6f

#define IsOCP1    (_IS_OCP())
#define IsOCP2    (IO>8)
#define IsOVP     (VBAT>60)
#define IsOTP     (TEMP>75)

#define IsProtection        (*State != MODE_OCP1 || *State != MODE_OCP2 || *State != MODE_OVP || *State != MODE_OTP)
#define IsBatteryCheck      (!IsProtection && VBAT_ADC<VMIN_ADC)
#define IsChargingRequest   (*State == MODE_BATTERY_CHECK && VBAT_ADC > VMIN_ADC && VBAT_ADC < VFLOAT_ADC)
#define IsSoftStart         (*State == MODE_CHARGING_REQUEST)
#define IsHandShake         (*State == MODE_SOFT_START && VO_ADC>(VBAT_ADC+1))
#define IsCharging          (*State == MODE_HAND_SHAKE && HSHKOK)
#define IsFullyCharged      (*State == MODE_CHARGING && IO_ADC < IMIN_ADC && VO_ADC >= VMAX_ADC)


#define IsPreCharge         ((VBAT>VMIN) && (VBAT<VDDCHRG))                                         //Stage 1
#define IsBulkCharge        ((Charging_Stage == PRECHARGE) && (VBAT>=VDDCHRG) && (VBAT<VBULK))   //Stage 2 (CC)
#define IsFloatCharge       ((Charging_Stage == FULL) && VBAT<=VFLOAT)                           //Stage 3
#define IsFull              (Charging_Stage == BULKCHARGE && VBAT>=VBULK && IBAT<=IMIN)


void CHRGR_manageOperationProtectings(Operating_Mode *Operation_State, float VBAT, float VO, float IO, float TEMP);
void CHRGR_executeProtection();
void CHRGR_manageOperationStates(Operating_Mode *State, uint16_t VBAT, uint16_t VO, uint16_t IO, uint16_t TEMP);
void CHRGR_executeBatteryCheckState(void);
void CHRGR_executeHandShakeState(bool *HSHKOK);
void CHRGR_executeFullyChargedState();
float CTRL_getPIController(float error, float *integral, float Kp, float Ki, float highlimit, float lowlimit);
float CTRL_getVIDualLoopControlledFx_LLC(float VO, float IO, ControllerParams_LLC CTRL_Params);
void CTRL_resetVIDualLoopController();
void CTRL_lookupAdaptiveControllerParameterTable(float VO, float Tsp, float *Kp, float *Ki);
void CHRGR_executeChargingState(uint16_t VBAT_ADC, uint16_t VO_ADC, uint16_t IO_ADC, uint16_t TEMP_ADC);
void PRFL_lookup3StageCharging(float VBAT, float IBAT, ChargingStage *Stage, float *VREF, float *IREFmax, uint16_t *IsCharged, int *TIME);
void CTRL_getRAMPUPValue(float input, float step, float *output);
#endif /* APP_EBIKECHARGER_H_ */
