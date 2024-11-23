/*
 * Profile.c
 *
 *  Created on: 12 Mar 2024
 *      Author: DELL
 */

#include <cal_Profile.h>

uint16_t _PRFL_lookup3StageCharging(uint32_t vbat_q14, uint32_t ibat_q14, ChargingProfileParams *CHARGINGPARAMS){
    static ChargingStage Charging_Stage = PRECHARGE;
    uint32_t RAMPUPSTEP = 2;

    const uint32_t VBULK_q14    = _TO_FIX(VBULK, Q);
    const uint32_t VFLOAT_q14   = _TO_FIX(VFLOAT, Q);
    const uint32_t VDDCHRG_q14  = _TO_FIX(VDDCHRG, Q);
    const uint32_t VMIN_q14     = _TO_FIX(VMIN, Q);
    const uint32_t IBULK_q14    = _TO_FIX(IBULK, Q);
    const uint32_t IPRE_q14     = _TO_FIX(IPRE, Q);
    const uint32_t IMIN_q14     = _TO_FIX(IMIN, Q);
    static int iRampUp = 0;

    if (ibat_q14<(IMIN_q14>>1)) iRampUp = IMIN_q14;

    //START Check Charging Stage
    if (_IS_PRECHARGE())                Charging_Stage = PRECHARGE;
    else if (_IS_BULK_CHARGE())         Charging_Stage = BULKCHARGE;
//    else if (IsFull)            Charging_Stage = Full;
    //END Check Charging Stage

    //START Do Charging Stage
    switch (Charging_Stage) {
        case PRECHARGE:
            CHARGINGPARAMS->voltage = VBULK_q14;
            //_CTRL_Get_Ramp_Up_Value(IPRE_q14, RAMPUPSTEP, &iRampUp);
            CHARGINGPARAMS->current = IBULK_q14;
            CHARGINGPARAMS->time = TIMEOUT_PRECHARGE;
            break;
        case BULKCHARGE:
            CHARGINGPARAMS->voltage = VBULK_q14;
            //_CTRL_Get_Ramp_Up_Value(IBULK_q14, RAMPUPSTEP, &iRampUp);
            CHARGINGPARAMS->current = IBULK_q14;
            if(vbat_q14<VBULK_q14){
                CHARGINGPARAMS->time = TIMEOUT_BULKCHARGE1;
            }
            else{
                CHARGINGPARAMS->time = TIMEOUT_BULKCHARGE2;
            }
            break;
//        case Full:
//            CHARGINGPARAMS->voltage = VBULK_q14;
//            CHARGINGPARAMS->current = IPRE_q14;
//            CHARGINGPARAMS->time = 3600;
//            CHARGINGPARAMS->status = 0;
//            break;
        default:
            break;
    }
    //END Do Charging Stage
    return Charging_Stage;
}

uint16_t _PRFL_lookup3StageCharging_modified_Q(uint32_t vbat_q14, uint32_t ibat_q9, ChargingProfileParams *CHARGINGPARAMS){
    static ChargingStage Charging_Stage = PRECHARGE;
    uint32_t RAMPUPSTEP = 2;

    const uint32_t VBULK_q14    = _TO_FIX(VBULK, Q);
    const uint32_t VFLOAT_q14   = _TO_FIX(VFLOAT, Q);
    const uint32_t VDDCHRG_q14  = _TO_FIX(VDDCHRG, Q);
    const uint32_t VMIN_q14     = _TO_FIX(VMIN, Q);
    const uint32_t IBULK_q9    = _TO_FIX(IBULK, Q_Hai);
    const uint32_t IPRE_q9     = _TO_FIX(IPRE, Q_Hai);
    const uint32_t IMIN_q9     = _TO_FIX(IMIN, Q_Hai);
    static int iRampUp = 0;

    if (ibat_q9<(IMIN_q9>>1)) iRampUp = IMIN_q9;

    //START Check Charging Stage
    if (_IS_PRECHARGE_MOD_Q())                Charging_Stage = PRECHARGE;
    else if (_IS_BULK_CHARGE_MOD_Q())         Charging_Stage = BULKCHARGE;
//    else if (IsFull)            Charging_Stage = Full;
    //END Check Charging Stage

    //START Do Charging Stage
    switch (Charging_Stage) {
        case PRECHARGE:
            CHARGINGPARAMS->voltage = VBULK_q14;
            _CTRL_Get_Ramp_Up_Value(IPRE_q9, RAMPUPSTEP, &iRampUp);
            CHARGINGPARAMS->current = iRampUp;
            CHARGINGPARAMS->time = TIMEOUT_PRECHARGE;
            break;
        case BULKCHARGE:
            CHARGINGPARAMS->voltage = VBULK_q14;
            _CTRL_Get_Ramp_Up_Value(IBULK_q9, RAMPUPSTEP, &iRampUp);
            CHARGINGPARAMS->current = iRampUp;
            if(vbat_q14<VBULK_q14){
                CHARGINGPARAMS->time = TIMEOUT_BULKCHARGE1;
            }
            else{
                CHARGINGPARAMS->time = TIMEOUT_BULKCHARGE2;
            }
            break;
//        case Full:
//            CHARGINGPARAMS->voltage = VBULK_q14;
//            CHARGINGPARAMS->current = IPRE_q14;
//            CHARGINGPARAMS->time = 3600;
//            CHARGINGPARAMS->status = 0;
//            break;
        default:
            break;
    }
    //END Do Charging Stage
    return Charging_Stage;
}

uint32_t PRFL_getTemperatureDeratingCurrent(uint16_t temp_ADC){
    static uint32_t Temperature_Sampling_Time = 0;
    const uint16_t HIGHTEMP_ADC = (uint16_t)((HIGHTEMP - 40)*25 + 2600);
    const uint16_t LOWTEMP_ADC  = (uint16_t)((LOWTEMP - 40)*25 + 2600);
    const uint16_t IBULK_ADC = (uint16_t)(IBULK/IBAT_GAIN);
    const uint16_t IPRE_ADC  = (uint16_t)(IPRE/IBAT_GAIN);
    uint16_t ihighlimit_ADC = IBULK_ADC;

    if (Temperature_Sampling_Time<TEMPERATURE_SAMPLING_CYCLE)
        Temperature_Sampling_Time++;
    else
    {
        if(_IS_DERATING())          ihighlimit_ADC = IBULK_ADC - 4*(temp_ADC - LOWTEMP_ADC);
        else if(_IS_NORMAL_TEMPERATURE())   ihighlimit_ADC = IBULK_ADC;
        else                    ihighlimit_ADC = IPRE_ADC;
    }
    return ihighlimit_ADC;
}

uint32_t PRFL_getTemperatureDeratingFAN(uint16_t temp_ADC){
    static uint32_t Temperature_Sampling_Time = 0;
    const uint16_t hightemp = 70;
    const uint16_t lowtemp = 60;
    const uint16_t HIGHTEMP_ADC = (uint16_t)((hightemp - 40)*25 + 2600);
    const uint16_t LOWTEMP_ADC  = (uint16_t)((lowtemp - 40)*25 + 2600);

    uint16_t fan_PWM = 0;

    if(temp_ADC<LOWTEMP_ADC)                                    fan_PWM = 450;
    else if(temp_ADC>=LOWTEMP_ADC && temp_ADC<=HIGHTEMP_ADC)    fan_PWM = 450 + (temp_ADC - LOWTEMP_ADC);
    else if(temp_ADC>HIGHTEMP_ADC)                              fan_PWM = 700;

    return fan_PWM;
}

