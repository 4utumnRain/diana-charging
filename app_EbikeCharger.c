/*
 * Ebike_Charger.c
 *
 *  Created on: 16 Nov 2023
 *      Author: DELL
 */

#include <app_EbikeCharger.h>

void _CHRGR_Manage_Charger_Operations_State(uint16_t vbat_ADC, uint16_t vo_ADC, uint16_t ibat_ADC, uint16_t temp_ADC){
    const uint16_t VMAX_ADC     = (uint16_t)(VMAX/VBAT_GAIN);
    const uint16_t IMAX_ADC     = (uint16_t)(IMAX/IBAT_GAIN);
    const uint16_t VLOW_ADC     = (uint16_t)(VLOW/VBAT_GAIN);
    const uint16_t VMIN_ADC     = (uint16_t)(VMIN/VBAT_GAIN);
    const uint16_t VBULK_ADC    = (uint16_t)(VBULK/VBAT_GAIN);
    const uint16_t VFLOAT_ADC   = (uint16_t)(VFLOAT/VBAT_GAIN);
    const uint16_t VDDCHRG_ADC  = (uint16_t)(VDDCHRG/VBAT_GAIN);
    const uint16_t IPRE_ADC     = (uint16_t)(IPRE/IBAT_GAIN);
    const uint16_t TEMPMAX_ADC  = (uint16_t)((TEMPMAX - 40U)*25U + 2600U);
    const uint16_t TEMPINIT_ADC = (uint16_t)((TEMPINIT - 40U)*25U + 2600U);
    const uint32_t _18ms_ = 0.01f/Tz;
    const uint32_t _10ms_ = 0.01f/Tz;
    const uint32_t TRANSIENT_TIME = 100U;
    Operating_Mode previousState = Charger_State;
    static int CntOfIVP = 0U;
    static uint16_t TimCnt = 0U;

    TimCnt++;
    if (TimCnt >= _10ms_){
        WatchDog_Time += 1U;
        Global_Time += 1U;
        Charge_Time_10ms += 1U;
        TimCnt = 0U;
    }

    if (!_IS_PROTECTING())
    {
        if      (_IS_OVP()) {
            Charger_State = MODE_OVP;
        }
        else if (_IS_OCP1()) {
            Charger_State = MODE_OCP1;
        }
        else if (_IS_OCP2()) {
            Charger_State = MODE_OCP2;
        }
        else if (_IS_OTP()) {
            Charger_State = MODE_OTP;
        }
//        else if (_IS_PRECHARGING()) {
//            Charger_State = MODE_PRECHARGE;
//        }
        else if (_IS_BULK_CHARGING()) {
            Charger_State = MODE_BULK_CHARGE;
        }
        else if (_IS_BATTERY_CHECK()) {
            Charger_State = MODE_BATTERY_CHECK;
        }
        else if (_IS_CHARGING_REQUEST()) {
            Charger_State = MODE_CHARGING_REQUEST;
        }
        else if (_IS_SOFT_START()) {
            Charger_State = MODE_SOFT_START;
        }
        else if (_IS_HAND_SHAKE()) {
            Charger_State = MODE_HAND_SHAKE;
        }
        else if (_IS_FULLY_CHARGED()) {
            Charger_State = MODE_FULLY_CHARGED;
        }
        else {

        }
    }
    else if ( (Charger_State == MODE_OVP && !_IS_OVP())
            ||(Charger_State == MODE_OCP2 && !_IS_OCP2())
            ||(Charger_State == MODE_IVP && !_IS_IVP())
            ||(Charger_State == MODE_OTP && _IS_NOTP())
            ||(Charger_State == MODE_OCP1)) {
        if (!_PWM_STT() && !_LLC_RELAY_STT()){
            _OCP_CLR();
            if (Waiting(5U))Charger_State  = MODE_BATTERY_CHECK;
        }
    }
    if (Charger_State != previousState) {
        WatchDog_Time = 0U;
    }
}

void _CHRGR_Execute_Battery_Check_State(){
    _CTRL_Reset_Dual_Controller();
    Over_Time_Threshold = 3600U;
    _STOP_PWM();
    _LLC_RELAY_OFF();
    _FAN_OFF();
}

void _CHRGR_Execute_Soft_Start_State(){
    const uint32_t PERIOD = 160U;
    HAL_SoftStart(PERIOD, 50U, 24U);
    //HAL_setPFM(PERIOD, 50U, 24U);
    _START_PWM();
    return;
}
void CHRGR_executeHandShakeState(bool *HSHKOK){
    static int cnt = 0;
    const int STOPVALUE1 = 0.002/SamplingTime;
    const int STOPVALUE2 = 0.1/SamplingTime;
    _STOP_PWM();
    if (cnt>=STOPVALUE1){
        _LLC_RELAY_ON();
    }
    if (cnt>=STOPVALUE2){
        cnt = 0;
        *HSHKOK = true;
    }
    else cnt++;
}

void _CHRGR_Execute_HandShake_State(){
    static int Cnt = 0U;
    const int STOP_VALUE = 0.05f/Tz;
    if (_PWM_STT()){
        _STOP_PWM();
        Cnt = 0U;
    }
    if (Cnt >= STOP_VALUE) {
        _LLC_RELAY_ON();
        _FAN_ON();
    }
    else {
        Cnt++;
    }
}

void _CHRGR_Execute_Charging_State(uint16_t vbatADC, uint16_t voADC, uint16_t ibatADC, uint16_t tempADC){
    const uint32_t VBAT_GAIN_Q14 = _TO_FIX(VBAT_GAIN, Q);
    const uint32_t VBAT_Q14      = _FMULI(VBAT_GAIN_Q14, vbatADC);

    const uint32_t VO_GAIN_Q14   = _TO_FIX(VO_GAIN, Q);
    const uint32_t VO_Q14        = _FMULI(VO_GAIN_Q14, voADC);

    const uint32_t IBAT_GAIN_Q14 = _TO_FIX(IBAT_GAIN, Q);
    const uint32_t IBAT_Q14      = _FMULI(IBAT_GAIN_Q14, ibatADC);

    const uint32_t VBULK_Q14    = _TO_FIX(VBULK, Q);
    const uint32_t IMIN_Q14     = _TO_FIX(IMIN, Q);
    const uint32_t IBULK_Q14    = _TO_FIX(IBULK, Q);
    const uint32_t FxMIN_Q14    = _TO_FIX(FxMIN, Q);
    const uint32_t FxMAX_Q14    = _TO_FIX(FxMAX, Q);
    const uint32_t DMIN_Q14     = _TO_FIX(DMIN, Q);
    const uint32_t DMAX_Q14     = _TO_FIX(DMAX, Q);

    static ControllerParams ControlParams = {VBULK_Q14, IMIN_Q14, IBULK_Q14, FxMIN_Q14, FxMAX_Q14, DMIN_Q14, DMAX_Q14, false};
    ChargingProfileParams chargingParams;

    _PRFL_lookup3StageCharging(VBAT_Q14, IBAT_Q14, &chargingParams);
    ControlParams.vref      = chargingParams.voltage;
    ControlParams.irefmax   = chargingParams.current;
    _CHRGR_Set_Over_Time_Threshold(chargingParams.time);

    _START_PWM();
    ControlParams.Status = true;

    uint32_t iHighLimitQ14 = _FMULI(IBAT_GAIN_Q14, PRFL_getTemperatureDeratingCurrent(tempADC));
    if (ControlParams.irefmax > iHighLimitQ14)   ControlParams.irefmax = iHighLimitQ14;

//    uint32_t PWM_Period = CTRL_getVIDualLoopControlledFx(vbat_q15, ibat_q15, CONTROLPARAMS);
//    HAL_setPFM(PWM_Period, 50, 24);
    _CTRL_getFxDfromVIDualLoopController(VBAT_Q14, IBAT_Q14, ControlParams);
}

void _CHRGR_Execute_Charging_State_with_Modified_Q(uint16_t vbatADC, uint16_t voADC, uint16_t ibatADC, uint16_t tempADC){
    const uint32_t VBAT_GAIN_Q14 = _TO_FIX(VBAT_GAIN, Q);
    const uint32_t VBAT_Q14      = _FMULI(VBAT_GAIN_Q14, vbatADC);

    const uint32_t VO_GAIN_Q14   = _TO_FIX(VO_GAIN, Q);
    const uint32_t VO_Q14        = _FMULI(VO_GAIN_Q14, voADC);

    const uint32_t IBAT_GAIN_Q14 = _TO_FIX(IBAT_GAIN, Q);
    const uint32_t IBAT_Q9      = FMUL(IBAT_GAIN_Q14, ibatADC, Q_diff);

    const uint32_t VBULK_Q14    = _TO_FIX(VBULK, Q_Hai);
    const uint32_t IMIN_Q9     = _TO_FIX(IMIN, Q_Hai);
    const uint32_t IBULK_Q9    = _TO_FIX(IBULK, Q_Hai);
    const uint32_t FMIN_Q9    = _TO_FIX(FMIN, Q_Hai);
    const uint32_t FMAX_Q9    = _TO_FIX(FMAX, Q_Hai);
    const uint32_t DMIN_Q9     = _TO_FIX(DMIN, Q_Hai);
    const uint32_t DMAX_Q9     = _TO_FIX(DMAX, Q_Hai);

    static ControllerParams_mod_Q ControlParams = {VBULK_Q14, IMIN_Q9, IBULK_Q9, FMIN_Q9, FMAX_Q9, DMIN_Q9, DMAX_Q9, false};
    ChargingProfileParams chargingParams;

    _PRFL_lookup3StageCharging_modified_Q(VBAT_Q14, IBAT_Q9, &chargingParams);
    ControlParams.vref      = chargingParams.voltage;
    ControlParams.irefmax   = chargingParams.current;
    _CHRGR_Set_Over_Time_Threshold(chargingParams.time);

    _START_PWM();
    ControlParams.Status = true;

    uint32_t iHighLimitQ9 = FMUL(IBAT_GAIN_Q14, PRFL_getTemperatureDeratingCurrent(tempADC),Q_diff);
    if (ControlParams.irefmax > iHighLimitQ9)   ControlParams.irefmax = iHighLimitQ9;

//    uint32_t PWM_Period = CTRL_getVIDualLoopControlledFx(vbat_q15, ibat_q15, CONTROLPARAMS);
//    HAL_setPFM(PWM_Period, 50, 24);

    //Tan so sample khi modify Q la 20kHz
    //Tan so sample khi chua modify Q la 50kHz
    //Cac tham so BDK khi modify Q duoc scale 5/2 lan
    _CTRL_getFxDfromVIDualLoopControllerWith100HzCalcelation(VBAT_Q14, IBAT_Q9, ControlParams);
}

void _CHRGR_Execute_System_Stop(){
    static int Cnt = 0U;
    const int STOP_VALUE = 0.05f/Tz;
    if (_PWM_STT()){
        _STOP_PWM();
        Cnt = 0;
    }
    if (Cnt >= STOP_VALUE){
        _LLC_RELAY_OFF();
        _FAN_OFF();
    }
    else Cnt++;
}


void _CHRGR_Execute_Open_Loop(uint16_t Fsw, uint16_t Duty, uint16_t Fixed_Deadtime){
    static uint16_t instantPeriod = 160U; //Maximum freq = 600kHz
    const uint16_t EndPeriod = Fsw; // Minimum freq = 150 kHz

    static uint16_t instantDeadtimeCntValue = 72U; //500ns
    const uint16_t endDeadtimeCntValue = (uint16_t)(Fixed_Deadtime*12U/100U);

    if(ISR_Delay_us(10000U, 20U)){
        if (instantPeriod < EndPeriod){
            instantPeriod++;
            if (instantDeadtimeCntValue > endDeadtimeCntValue) instantDeadtimeCntValue--;
            HAL_setPFM(instantPeriod, 50U, 24U);
        }
   }
}

void _CHRGR_Execute_Close_Loop(uint16_t vbat_ADC, uint16_t ibat_ADC){
    //Start Code for Close Loop
    const uint32_t VBATGAIN_q14 = _TO_FIX(VBAT_GAIN, Q);
    const uint32_t vbat_q14     = _FMULI(VBATGAIN_q14, vbat_ADC);

    const uint32_t IBATGAIN_q14 = _TO_FIX(IBAT_GAIN, Q);
    const uint32_t ibat_q14     = _FMULI(IBATGAIN_q14, ibat_ADC);

    const uint32_t VBULK_q14    = _TO_FIX(VBULK, Q);
    const uint32_t IMIN_q14     = _TO_FIX(IMIN, Q);
    const uint32_t IBULK_q14    = _TO_FIX(IBULK, Q);
    const uint32_t FxMIN_q14    = _TO_FIX(FxMIN, Q);
    const uint32_t FxMAX_q14    = _TO_FIX(FxMAX, Q);
    const uint32_t DMIN_q14     = _TO_FIX(DMIN, Q);
    const uint32_t DMAX_q14     = _TO_FIX(DMAX, Q);

    static ControllerParams CONTROLPARAMS = {VBULK_q14, IMIN_q14, IBULK_q14, FxMIN_q14, FxMAX_q14, DMIN_q14, DMAX_q14, false};
    if (WatchDog_Time > 200U){
        _LLC_RELAY_ON();
        _START_PWM();
        CONTROLPARAMS.Status = true;
        _CTRL_getFxDfromVIDualLoopController(vbat_q14, ibat_q14, CONTROLPARAMS);
    }
    //End Code for Close Loop
}


void _CHRGR_Set_LED_Indicator(uint16_t voADC)
{
    const uint16_t VFLOAT_ADC  = (uint16_t)(VFLOAT/VBAT_GAIN);
    const uint16_t VDDCHRG_ADC = (uint16_t)(VDDCHRG/VBAT_GAIN);
    const uint16_t VLOWEST_ADC = (uint16_t)(VLOWEST/VBAT_GAIN);
    const uint16_t VLOW_ADC     = (uint16_t)(VLOW/VBAT_GAIN);

    static Operating_Mode PreviousChargerState = MODE_BATTERY_CHECK;
    static int Cnt = 0U;

    if (PreviousChargerState!=Charger_State){
        HAL_setLEDsignals(0, 0, 0, 0);
        PreviousChargerState = Charger_State;
        Cnt = 0U;
    }

    if (Charger_State == MODE_BATTERY_CHECK){
        if (Delay_100us(UPDATE_LED_TIME)) {
            if ((voADC < VLOWEST_ADC)) {
                Cnt++;
                if (Cnt == 1U) {
                    HAL_setLEDsignals(1, 0, 0, 0);
                }
                else if (Cnt == 2U) {
                    HAL_setLEDsignals(0, 1, 0, 0);
                }
                else if (Cnt == 3U) {
                    HAL_setLEDsignals(0, 0, 1, 0);
                }
                else if (Cnt == 4U) {
                    HAL_setLEDsignals(0, 0, 0, 1);
                    Cnt = 0U;
                }
                else {
                    // NOT REACHED
                }
            }

            else if ((voADC > VLOWEST_ADC) && (voADC < VLOW_ADC)) {
                HAL_setLEDsignals(0, 1, 1, 0);
            }

            else if (voADC > VFLOAT_ADC) {
                HAL_setLEDsignals(1, 1, 1, 1);
            }

        }
    }
    else if ((Charger_State == MODE_CHARGING_REQUEST) || (Charger_State == MODE_SOFT_START) || (Charger_State == MODE_HAND_SHAKE)){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)){
            Cnt++;
            if (Cnt == 1U) {
                HAL_setLEDsignals(1, 0, 0, 0);
            }
            else if (Cnt == 2U) {
                HAL_setLEDsignals(0, 1, 0, 0);
            }
            else if (Cnt == 3U) {
                HAL_setLEDsignals(0, 0, 1, 0);
            }
            else if (Cnt == 4U) {
                HAL_setLEDsignals(0, 0, 0, 1);
                Cnt = 0U;
            }
        }
    }
    else if(Charger_State == MODE_PRECHARGE){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(1, 2, 0, 0);
        }
    }
    else if(Charger_State == MODE_BULK_CHARGE && voADC <= VFLOAT_ADC) {
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(1, 1, 2, 0);
        }
    }
    else if(Charger_State == MODE_BULK_CHARGE && voADC > VFLOAT_ADC) {
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(1, 1, 1, 2);
        }
    }
    else if(Charger_State==MODE_FULLY_CHARGED) {
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(1, 1, 1, 1);
        }
    }
    else if(Charger_State == MODE_OCP1 || Charger_State == MODE_OCP2){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(0, 1, 0, 0);
        }
    }
    else if(Charger_State==MODE_OVP){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(0, 0, 1, 0);
        }
    }
    else if(Charger_State==MODE_IVP){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(0, 0, 0, 1);
        }
    }
    else if(Charger_State == MODE_OTP){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) {
            HAL_setLEDsignals(2, 2, 2, 2);
        }
    }
    else if((Charger_State == MODE_OFP) || (Charger_State == ERR_HARDWARE)){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) HAL_setLEDsignals(2, 0, 0, 0);
    }
    else if(((Charger_State == ERR_PRECHARGE_TIMEOUT) || (Charger_State == MODE_OT)) && (voADC < VDDCHRG_ADC)){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) HAL_setLEDsignals(2, 1, 0, 0);
    }
    else if (((Charger_State == ERR_CHARGE_TIMEOUT) || (Charger_State == MODE_OT)) && (voADC > VDDCHRG_ADC)) {
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) HAL_setLEDsignals(2, 1, 1, 0);
    }
    else if(Charger_State==MODE_CLOSE_LOOP){
        if (Delay_100us(UPDATE_LED_TIME)) HAL_setLEDsignals(2, 0, 2, 0);
    }
    else if(Charger_State==MODE_OPEN_LOOP){
        if (Delay_100us(UPDATE_LED_TIME)) HAL_setLEDsignals(1, 2, 2, 2);
    }
}

void _CHRGR_Lastest_Err_LED_Indicator(Operating_Mode readChargerState)
{
    const uint16_t VFLOAT_ADC  = (uint16_t)(VFLOAT/VBAT_GAIN);
    const uint16_t VDDCHRG_ADC = (uint16_t)(VDDCHRG/VBAT_GAIN);
    const uint16_t VLOWEST_ADC = (uint16_t)(VLOWEST/VBAT_GAIN);
    const uint16_t VLOW_ADC     = (uint16_t)(VLOW/VBAT_GAIN);

    if(readChargerState == MODE_OCP1 || readChargerState == MODE_OCP2){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(0, 1, 0, 0);
        }
    }
    else if(readChargerState == MODE_OVP){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(0, 0, 1, 0);
        }
    }
    else if(readChargerState == MODE_IVP){
        if (Delay_100us(UPDATE_LED_TIME)) {
            HAL_setLEDsignals(0, 0, 0, 1);
        }
    }
    else if(readChargerState == MODE_OTP){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) {
            HAL_setLEDsignals(2, 2, 2, 2);
        }
    }
    else if((readChargerState == MODE_OFP) || (readChargerState == ERR_HARDWARE)){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) HAL_setLEDsignals(2, 0, 0, 0);
    }
    else if(readChargerState == ERR_PRECHARGE_TIMEOUT){
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) HAL_setLEDsignals(2, 1, 0, 0);
    }
    else if (Charger_State == ERR_CHARGE_TIMEOUT) {
        if (Delay_100us(UPDATE_LED_TIME >> 2U)) HAL_setLEDsignals(2, 1, 1, 0);
    }

}


char* _CHRGR_Get_Charger_State(Operating_Mode State)
{
    switch (State) {
        case MODE_CLOSE_LOOP:       return "CLOSE";
        case MODE_OPEN_LOOP:        return "OPEN";
        case MODE_BATTERY_CHECK:    return "BAT?";
        case MODE_CHARGING_REQUEST: return "RQUST";
        case MODE_SOFT_START:       return "SS";
        case MODE_HAND_SHAKE:       return "HS";
        case MODE_PRECHARGE:        return "PRE";
        case MODE_BULK_CHARGE:      return "BULK";
        case MODE_CHARGING:         return "CG";
        case MODE_FULLY_CHARGED:    return "FLL";

        case  MODE_IVP:   return "IVP";
        case  MODE_OVP:   return "OVP";
        case  MODE_OCP1:  return "OCP1";
        case  MODE_OCP2:  return "OCP2";
        case  MODE_OTP:   return "OTP";
        case  MODE_OT:    return "OT";
        case  MODE_OFP:   return "OFP";
        case  MODE_IDLE:  return "IDLE";
        case  MODE_READ_MEMORY : return "READ";
        case ERR_HARDWARE:       return "ERRHW";
        case ERR_PRECHARGE_TIMEOUT: return "PRET";
        case ERR_CHARGE_TIMEOUT:  return "CHRT";
        default: return "Unknown";
    }
}

void _CHRGR_Set_Over_Time_Threshold(int stopTime){
    Over_Time_Threshold = stopTime;
}

void _CHRGR_Reset_Charger()
{
    //_PFC_RELAY_OFF();
    _FAN_ON();
    WatchDog_Time = 0;
}
bool _Is_OTP(uint16_t tempAdc)
{
    const uint16_t TEMPMAX_ADC  = (uint16_t)((TEMPMAX - 40U)*25U + 2600U);
    static uint16_t OtpTimeOutCnt = 0U;
    if (tempAdc > TEMPMAX_ADC) {
        OtpTimeOutCnt++;
    }
    else {
        OtpTimeOutCnt = 0U;
    }

    if (OtpTimeOutCnt > OTP_TIMEOUT) {
        OtpTimeOutCnt = 0U;
        return true;
    }
    else {
        return false;
    }

}

bool _Is_OVP(uint16_t vbatAdc)
{
    const uint16_t VMAX_ADC     = (uint16_t)(VMAX/VBAT_GAIN);
    static uint16_t TimeOutCnt = 0U;
    if (vbatAdc > VMAX_ADC) {
        TimeOutCnt++;
    }
    else {
        TimeOutCnt = 0U;
    }

    if (TimeOutCnt > OVP_TIMEOUT) {
        TimeOutCnt = 0U;
        return true;
    }
    else {
        return false;
    }
}

//_IS_FULLY_CHARGED()      (Charger_State == MODE_BULK_CHARGE && vbat_ADC >= VBULK_ADC && ibat_ADC < IPRE_ADC)
bool _Is_Fully_Charged(uint16_t vbatAdc, uint16_t ibatAdc)
{
    const uint16_t VBULK_ADC    = (uint16_t)(VBULK/VBAT_GAIN);
    const uint16_t IPRE_ADC     = (uint16_t)(IPRE/IBAT_GAIN);
    static uint16_t TimeOutCnt = 0U;
    if ((Charger_State == MODE_BULK_CHARGE) && (vbatAdc >= VBULK_ADC) && (ibatAdc < IPRE_ADC)) {
        TimeOutCnt++;
    }
    else {
        TimeOutCnt = 0U;
    }

    if (TimeOutCnt > FLL_CHRG_TIMEOUT) {
        TimeOutCnt = 0U;
        return true;
    }
    else {
        return false;
    }

}

void _CHRGR_Execute_Charging_State_CurrentLoop_NotIQMath(float vbat, float vo, float ibat){
    _START_PWM();
    _CTRL_getFxDfromIController_NoIQMath(ibat,IBULK);
}

void _CHRGR_Execute_Charging_State_DualVILoop_NotIQMath(float vbat, float vo, float ibat){
    _START_PWM();
    _CTRL_getFxDfromDualVIController_NoIQMath(vbat,ibat);
}

/*------------------------ My definitions ---------------------------*/

void CHRGR_executeProtection(){
    _LLC_RELAY_OFF();
    _STOP_PWM();
}

void CHRGR_manageOperationProtectings(Operating_Mode *Operation_State, float VBAT, float VO, float IO, float TEMP)
{
    if (IsOCP1){          /* Over Primary Current Protect */
        *Operation_State = MODE_OCP1;
        CHRGR_executeProtection();
    }
    else if (IsOCP2){     /* Over Power Protect */
        *Operation_State = MODE_OCP2;
        CHRGR_executeProtection();
    }
    else if (IsOVP){      /* Over Output Voltage Protect */
        *Operation_State = MODE_OVP;
        CHRGR_executeProtection();
    }
//    else if (IsOTP){      /* Over Temperature Protect */
//        *Operation_State = tagOTP;
//        CHRGR_executeProtection();
//    }
}

void CHRGR_manageOperationStates(Operating_Mode *State, uint16_t VBAT_ADC, uint16_t VO_ADC, uint16_t IO_ADC, uint16_t TEMP_ADC)
{
    const uint16_t VMAX_ADC     = (uint16_t)(VMAX/VBAT_GAIN);
    const uint16_t IMAX_ADC     = (uint16_t)(IMAX/IBAT_GAIN);
    const uint16_t IMIN_ADC     = (uint16_t)(IMIN/IBAT_GAIN);
    const uint16_t VLOW_ADC     = (uint16_t)(VLOW/VBAT_GAIN);
    const uint16_t VMIN_ADC     = (uint16_t)(VMIN/VBAT_GAIN);
    const uint16_t VBULK_ADC    = (uint16_t)(VBULK/VBAT_GAIN);
    const uint16_t VFLOAT_ADC   = (uint16_t)(VFLOAT/VBAT_GAIN);
    const uint16_t VDDCHRG_ADC  = (uint16_t)(VDDCHRG/VBAT_GAIN);
    const uint16_t IPRE_ADC     = (uint16_t)(IPRE/IBAT_GAIN);
    const uint16_t TEMPMAX_ADC  = (uint16_t)((TEMPMAX - 40U)*25U + 2600U);
    const uint16_t TEMPINIT_ADC = (uint16_t)((TEMPINIT - 40U)*25U + 2600U);

    static bool HSHKOK = false;

    if (IsBatteryCheck)         *State = MODE_BATTERY_CHECK;
    else if(IsChargingRequest)  *State = MODE_CHARGING_REQUEST;
    else if(IsSoftStart)        *State = MODE_SOFT_START;
    else if(IsHandShake)        *State = MODE_HAND_SHAKE;
    else if(IsCharging)         *State = MODE_CHARGING;
    else if(IsFullyCharged)     *State = MODE_FULLY_CHARGED;

    // START doing the operation state
    switch (*State) {
        case MODE_BATTERY_CHECK:
            HSHKOK = false;
            onetime_integral_frequency = false;
            CHRGR_executeBatteryCheckState();
            break;
        case MODE_CHARGING_REQUEST:
            CTRL_resetVIDualLoopController();
            break;
        case MODE_SOFT_START:
            _CHRGR_Execute_Soft_Start_State();
            break;
        case MODE_HAND_SHAKE:
            CHRGR_executeHandShakeState(&HSHKOK);
            onetime_integral_frequency = true;
            break;
        case MODE_CHARGING:
            //CHRGR_executeChargingState(VBAT_ADC, VO_ADC, IO_ADC, TEMP_ADC);
            //_START_PWM();
            _CHRGR_Execute_Charging_State_with_Modified_Q(VBAT_ADC, VO_ADC, IO_ADC, TEMP_ADC);
            break;
//        case MODE_FULLY_CHARGED:
//            //CHRGR_executeFullyChargedState();
//            //CHRGR_executeChargingState(VBAT, VO, IO, TEMP);
//            //_START_PWM();
//            break;
        default:
            break;
    }

    // STOP doing the operation state
    return;
}

void CHRGR_executeBatteryCheckState(void){
//    CHRGR_watchdogTimer(0);
    static int cnt = 0;
    const int STOPVALUE = 0.1/SamplingTime;
    _STOP_PWM();
    HAL_setPFM(160, 50, 48);
    if (cnt>=STOPVALUE){
        cnt = 0;
        _LLC_RELAY_OFF();
    }
    else if (!_LLC_RELAY_STT()) cnt++;
}

void CHRGR_executeFullyChargedState(){
    _STOP_PWM();
    _LLC_RELAY_OFF();
    _FAN_OFF();
}

void CTRL_resetVIDualLoopController(){
    ControllerParams_mod_Q CTRL_Params = {0, 0, 0, 0, 0, 0, 0, false};
    //CTRL_getVIDualLoopControlledFx_LLC(0, 0, CTRL_Params);
    _CTRL_getFxDfromVIDualLoopControllerWith100HzCalcelation(0, 0, CTRL_Params);
}

float CTRL_getVIDualLoopControlledFx_LLC(float VBAT, float IO, ControllerParams_LLC CTRL_Params){
    static float II = FxMAX;
//    int onetime = 1;
//    if (onetime){
//        float Frequency_n = TOFIX((float) (533/(float)DL_Timer_getLoadValue(PWM_0_INST)), );
//        II = Frequency_n;
//        onetime = 0;
//    }
    float Fx;
    if (CTRL_Params.Status){
        /*-----------------Voltage Loop------------------*/
        const float KiV_x_Tz = 100.0*CTRL_Params.Tsp;
        static float IV = 1.0f;
        float EV = CTRL_Params.Vref - VBAT;
        float IREF = CTRL_getPIController(EV, &IV, 0, KiV_x_Tz, CTRL_Params.Irefmax, CTRL_Params.Irefmin);

        /*-----------------Current Loop------------------*/
        float KpI, KiI;
        CTRL_lookupAdaptiveControllerParameterTable(VBAT, CTRL_Params.Tsp, &KpI, &KiI);
        float EI = IO - IREF;
        Fx = CTRL_getPIController(EI, &II, KpI, KiI, CTRL_Params.CtrlVarmax, CTRL_Params.CtrlVarmin);
    }
    else {
        II = CTRL_Params.CtrlVarmax;
        Fx = CTRL_Params.CtrlVarmax;
    }
    return Fx;
}

float CTRL_getPIController(float error, float *integral, float Kp, float Ki, float highlimit, float lowlimit){
    float I = *integral + Ki*error;
    float Output = Kp*error + I;
//    flagx = Kp + 10;
    if (Output>highlimit)       Output = highlimit;
    else if (Output<lowlimit)   Output = lowlimit;
    else *integral = I;
    return Output;
}


void CTRL_lookupAdaptiveControllerParameterTable(float VO, float Tsp, float *Kp, float *Ki){
    //const float32_t Kp_Level[5] = {97.0e-4f, 97.0e-4f, 97.0e-4f, 97.0e-4f, 97.0e-4f};
    const float Kp_Level[5] = {0.0f, 46.0e-4f, 46.0e-4f, 46.0e-4f, 46.0e-4f};
    const float wp_x_Tsp = 13237*Tsp;
    const float Ki_Level[5] = {10.0e-4*wp_x_Tsp, Kp_Level[1]*wp_x_Tsp, Kp_Level[2]*wp_x_Tsp, Kp_Level[3]*wp_x_Tsp, Kp_Level[4]*wp_x_Tsp};
    const float VO_Level[5] = {58.0f, 62.5f, 65.0f, 67.5f, 70.0f};

    int i;
    for (i = 0; i < 5; ++i){
        if (VO<VO_Level[i]){
            *Kp = Kp_Level[i];
            *Ki = Ki_Level[i];
            break;
        }
    }
    *Kp = 0.0e-4f;
    *Ki = 13.33e-4f;
}

void CHRGR_executeChargingState(uint16_t VBAT_ADC, uint16_t VO_ADC, uint16_t IO_ADC, uint16_t TEMP_ADC){
    static ControllerParams_LLC CTRL_Params = {VBULK, IMIN, IBULK, FxMIN, FxMAX, SamplingTime, false};
    ChargingStage currentStage = FULL;
    uint16_t CHRGFLG = false;
    int limitedTime;

    PRFL_lookup3StageCharging(VBAT_ADC, IO_ADC,&currentStage, &CTRL_Params.Vref, &CTRL_Params.Irefmax, &CHRGFLG, &limitedTime);
    if (CHRGFLG != CTRL_Params.Status){
        if (CHRGFLG)    {_START_PWM();  _LLC_RELAY_ON();}
        else            {_STOP_PWM();   _LLC_RELAY_OFF();}
    }
    CTRL_Params.Status = CHRGFLG;
    // FCLK = 80MHz, Fr = 150kHz --> FCLK/Fr = 533
    uint32_t PWM_Period = 533/CTRL_getVIDualLoopControlledFx_LLC(VBAT_ADC, IO_ADC, CTRL_Params);
    HAL_setPFWM(PWM_Period, 50, 24);
}

void PRFL_lookup3StageCharging(float VBAT, float IBAT, ChargingStage *Stage, float *VREF, float *IREFmax, uint16_t *IsCharged, int *TIME){
    static ChargingStage Charging_Stage = PRECHARGE;
    const float RAMPUPSTEP = 0.0005f;
    if (IBAT<(0.5*IMIN)) *IREFmax = IMIN;

    //START Check Charging Stage
    if (IsPreCharge)            Charging_Stage = PRECHARGE;
    else if (IsBulkCharge)      Charging_Stage = BULKCHARGE;
    else if (IsFloatCharge)     Charging_Stage = FLOATCHARGE;
    else if (IsFull)            Charging_Stage = FULL;
    //END Check Charging Stage
    //flagx = Charging_Stage;
    //START Do Charging Stage
    switch (Charging_Stage) {
        case PRECHARGE:
            *VREF = VBULK;
            CTRL_getRAMPUPValue(IPRE, RAMPUPSTEP, IREFmax);
            //*IREFmax = IPRE;
            *IsCharged = 1;
            *TIME = 7200;
            break;
        case BULKCHARGE:
            *VREF = VBULK;
            CTRL_getRAMPUPValue(IBULK, RAMPUPSTEP, IREFmax);
            //*IREFmax = IBULK;
            *IsCharged = 1;
            *TIME = 30000;
            break;
        case FLOATCHARGE:
            *VREF = VBULK;
            *IREFmax = IBULK;
            *IsCharged = 1;
            *TIME = 0;
            break;
        case FULL:
            *VREF = VBULK;
            *IREFmax = IBULK;
            *IsCharged = 0;
            *TIME = 0;
        default:
            break;
    }
    *Stage = Charging_Stage;
    //flagx = *Stage;
}

void CTRL_getRAMPUPValue(float input, float step, float *output){
    if (input>*output) *output += step;
}
