/*
 * Controller.c
 *
 *  Created on: 12 Mar 2024
 *      Author: DELL
 */

#include <cal_Controller.h>

const float b1   = (float)1/Qop/wop;
const float b2   = (float)1/wop/wop;
const float a1   = (float)1/Qoz/woz;
const float a2   = (float)1/woz/woz;

/* Constant values in QR BW Digitalization */

const float w = 1 + 2*b1/Tz + 4*b2/Tz/Tz;
const float w1 = 2 - 8*b2/Tz/Tz;
const float w2 = 1 - 2*b1/Tz + 4*b2/Tz/Tz;

const float v = 1 + 2*a1/Tz + 4*a2/Tz/Tz;
const float v1 = 2 - 8*a2/Tz/Tz;
const float v2 = 1 - 2*a1/Tz + 4*a2/Tz/Tz;

const float v_d_w = v/w;
const float v1_d_w = v1/w;
const float v2_d_w = v2/w;
const float w1_d_w = w1/w;
const float w2_d_w = w2/w;

const int f_v_d_w_q12  = _TO_FIX(v_d_w, QN);
const int f_v1_d_w_q12= _TO_FIX(v1_d_w, QN);
const int f_v2_d_w_q12 = _TO_FIX(v2_d_w, QN);
const int f_w1_d_w_q12 = _TO_FIX(w1_d_w, QN);
const int f_w2_d_w_q12 = _TO_FIX(w2_d_w, QN);

void _CTRL_Get_Ramp_Up_Value(int input, int step, int *output){
    if (input > *output) {
        *output += step;
    }
}

uint32_t CTRL_getVIDualLoopControlledFx(int vbatQ14, int ibatQ14, ControllerParams CTRL_Params){
    int irefMaxQ14 = CTRL_Params.irefmax;
    int irefMinQ14 = CTRL_Params.irefmin;
    static int IvQ14 = 16384U;
    const int  KIV_Q14 = 100U;

    int fxMaxQ14 = CTRL_Params.Fxmax;
    int fxMinQ14 = CTRL_Params.Fxmin;
    static int IiQ14 = 32768U;
    int kpiQ14 = 82U;
    int kiiQ14 = 204U;

    int vrefQ14 = CTRL_Params.vref;
    int fxQ14;

    if (CTRL_Params.Status){
        /*-----------------Voltage Loop------------------*/
        int evQ14 = vrefQ14 - vbatQ14;
        int irefQ14 = _CTRL_Get_PI_Controller(evQ14, &IvQ14, 0U, KIV_Q14, irefMaxQ14, irefMinQ14);
        /*-----------------Current Loop------------------*/
        _CTRL_Lookup_Adaptive_Controller_Parameters_Table(vbatQ14, &kpiQ14, &kiiQ14);
        int eiQ14 = ibatQ14 - irefQ14;
        fxQ14 = _CTRL_Get_PI_Controller(eiQ14, &IiQ14, 0, kiiQ14, fxMaxQ14, fxMinQ14);

    }
    else {
        IiQ14 = fxMaxQ14;
        fxQ14 = fxMaxQ14;
        IvQ14 = 16384U;
    }

    uint32_t period = 5242880U/fxQ14;
    return period;
}

uint32_t _CTRL_getFxDfromVIDualLoopController(int vbat_q14, int ibat_q14, ControllerParams CTRL_Params){
    int irefmax_q14 = CTRL_Params.irefmax;
    int irefmin_q14 = CTRL_Params.irefmin;
    static int iv_q14 = 16384;
    const int  KIVxTZ_q14 = 10;

    int fxmax_q14 = CTRL_Params.Fxmax;
    int fxmin_q14 = CTRL_Params.Fxmin;

    int dxmax_q14 = CTRL_Params.Dmax;
    int dxmin_q14 = CTRL_Params.Dmin;

    int x = 0, y = 0;
    static int x1 = 0, y1 = 0;
    static int iif_q14 = 0;
    int onetime = 1;
    if (onetime){
        int Frequency_q14 = (int16_t)(8732672/DL_Timer_getLoadValue(PWM_0_INST));
        iif_q14 = Frequency_q14;
        onetime = 0;
    }
    //static int iif_q14 = 32768;             // Initial Integral 500 kHz, -> 2 -> 2^14 -> 32768
    static int iid_q14 = 8192;
    int KPI_q14 = 0.0;
    int KII_q14 = 22;
    const int KII_D_q14 = 82;

    int vref_q14 = CTRL_Params.vref;
    static int fx_q14;
    static int dx_q14 = 8192;
    static int mode = 0;

    static int ibatLPF_q14 = 0;
    ibatLPF_q14 = ibat_q14 + FMUL(ibatLPF_q14 - ibat_q14, 5679, 14); //Tan so loc la 15kHz

    if (CTRL_Params.Status){
        /*-----------------Voltage Loop------------------*/
        int ev_q14 = vref_q14 - vbat_q14;
        int iref_q14 = _CTRL_Get_PI_Controller(ev_q14, &iv_q14, 0, KIVxTZ_q14, irefmax_q14, irefmin_q14);
        /*-----------------Current Loop------------------*/
        int ei_q14 = ibatLPF_q14 - iref_q14;
        /*------*/
        if (mode==0 && fx_q14>=fxmax_q14 && ei_q14>=0)      mode = 1;
        else if (mode==1 && dx_q14>=dxmax_q14 && ei_q14<=0) mode = 0;

        if (mode==0){
            _CTRL_Lookup_Adaptive_Controller_Parameters_Table(vbat_q14, &KPI_q14, &KII_q14);
             x = _CTRL_Get_PI_Controller(ei_q14, &iif_q14, KPI_q14, KII_q14, fxmax_q14, fxmin_q14);
//             x1 = x + FMUL(x1 - x, 15982, 14);
//             y = (x - x1)<<5;
//             y1 = y + FMUL(y1 - y, 16282, 14);
             fx_q14 = x;// + y1;
        }
        else if (mode==1){
            dx_q14 = _CTRL_Get_PI_Controller(-ei_q14, &iid_q14, 0, KII_D_q14, dxmax_q14, dxmin_q14);
        }
    }
    else {
        iif_q14 = fxmax_q14;
        fx_q14 = fxmax_q14;
        iid_q14 = dxmax_q14;
        dx_q14 = dxmax_q14;
    }

    uint32_t Period = 8732672/fx_q14;
    uint32_t Duty = (uint32_t)((dx_q14*Period)>>14);

    HAL_setPFWM(Period, Duty, 24);

    return 1;
}

uint32_t _CTRL_getFxDfromVIDualLoopControllerWith100HzCalcelation(int vbat_q14, int ibat_q9, ControllerParams_mod_Q CTRL_Params)
{
    int irefmax_q9 = CTRL_Params.irefmax;
    int irefmin_q9 = CTRL_Params.irefmin;
    static int iv_q14 = 16384U;
    const int  KIVxTZ_q14 = 25U;

    int fmax_q9 = CTRL_Params.Fmax;
    int fmin_q9 = CTRL_Params.Fmin;

    int dxmax_q9 = CTRL_Params.Dmax;
    int dxmin_q9 = CTRL_Params.Dmin;

    int x = 0, y = 0;
    static int x1 = 0, y1 = 0;
    uint32_t initial_frequency = 0;

    //static int iif_q9 = initial_frequency;
    static int iif_q9 = 256000000; //f=fr=250000 Hz Truoc: Q14 va dau ra Fn thi tham so nay la 32678 ung voi Fn = 2
    static int iid_q9 = 256; //Truoc: Q14 va dau ra Fn thi tham so nay la 8192
    int KPI_q9 = 0; //Truoc: Q14 va dau ra Fn thi tham so nay la 82, tham so cu 640625
    int KII_q9 = 100000; //Truoc: Q14 va dau ra Fn thi tham so nay la 204, tham so cu 1593750
    const int KII_D_q9 = 2; //Truoc: Q14 va dau ra Fn thi tham so nay la 82

    /* one time for updating the near frequency */
    if (onetime_integral_frequency){
        iif_q9 = _TO_FIX(((uint32_t)(80000000/ DL_Timer_getLoadValue(PWM_0_INST))), Q);
        onetime_integral_frequency = false;
    }

    int vref_q14 = CTRL_Params.vref;
    static int f_q9;
    static int dx_q9 = 256; //Truoc: Q14 va dau ra Fn thi tham so nay la 8192
    static int mode = 0;

    static int ibatLPF_q9 = 0;
    ibatLPF_q9 = ibat_q9 + FMUL(ibatLPF_q9 - ibat_q9, 5679, Q); //Gain ung voi tan so sample 20kHz, tan so loc 15

    if (CTRL_Params.Status)
    {
        /*-----------------Voltage Loop------------------*/
        int ev_q14 = vref_q14 - vbat_q14;
        int iref_q9 = _CTRL_Get_PI_V_Controller_modified_Q(ev_q14, &iv_q14, 0, KIVxTZ_q14, irefmax_q9, irefmin_q9);
        /*-----------------Current Loop------------------*/
        int ei_q9 = ibatLPF_q9 - iref_q9;
        /*------*/
        if (mode==0 && f_q9>=fmax_q9 && ei_q9 >= 0)      mode = 1;
        else if (mode==1 && dx_q9 >= dxmax_q9 && ei_q9 <=0) mode = 0;

        if (mode==0)
        {
            //_CTRL_Lookup_Adaptive_Controller_Parameters_Table(vbat_q9, &KPI_q9, &KII_q9);
             x = _CTRL_Get_PI_Controller_modified_Q(ei_q9, &iif_q9, KPI_q9, KII_q9, fmax_q9, fmin_q9);
//             x1 = x + FMUL(x1 - x, 15982, 14);
//             y = (x - x1)<<5;
//             y1 = y + FMUL(y1 - y, 16282, 14);
             f_q9 = x; // + y1;
        }
        else if (mode==1)
        {
            dx_q9 = _CTRL_Get_PI_Controller_modified_Q(-ei_q9, &iid_q9, 0, KII_D_q9, dxmax_q9, dxmin_q9);
        }
    }
    else {
        iif_q9 = fmax_q9;
        f_q9 = fmax_q9;
        iid_q9 = dxmax_q9;
        dx_q9 = dxmax_q9;
    }

    uint32_t f_q0 = f_q9 >> 9;

    uint32_t Period = 80000000/f_q0;
    uint32_t Duty = (uint32_t)((dx_q9*Period)>>9);

    HAL_setPFWM(Period, Duty, 24);

    return 1;
}

void _CTRL_Lookup_Adaptive_Controller_Parameters_Table(int vbat_q14, int *KPI_q14, int *KII_q14){
    const int VBATAXIS_q14[8]  = {901120, 933888, 966656, 999424, 1032192, 1097728, 1163264, 1212416}; //{55, 57, 59, 61, 63, 67, 71, 74}
//    const int KPIAXIS_q15[8]   = {240, 240, 180, 150, 120, 110, 90, 80};
//    const int KIIAXIS_q15[8]   = {24, 24, 18, 15, 12, 11, 9, 8};
    const int KPIAXIS_q14[8]   = {0, 0, 0, 0, 0, 0, 0, 0};
    const int KIIAXIS_q14[8]   = {22, 22, 22, 22, 22, 22, 22, 22};
    int i;

    for (i = 0; i < 8; ++i) {
        if (vbat_q14<VBATAXIS_q14[i]){
//            *KPI_q14 = KPIAXIS_q14[i];
//            *KII_q14 = KIIAXIS_q14[i];
              *KPI_q14 = 0.0;
              *KII_q14 = 22;
            break;
        }
    }
}

uint32_t _CTRL_Get_PI_Controller(int e, int *integral, int KP, int KI, int highlimit, int lowlimit){
    int integralx_q14 = *integral + FMUL(KI, e, Q);
    int propotional_q14 = FMUL(KP, e, Q);
    int output_q14 = propotional_q14 + integralx_q14;
    if (output_q14>highlimit){
        output_q14 = highlimit;
        *integral = highlimit - propotional_q14;
    }
    else if (output_q14<lowlimit){
        output_q14 = lowlimit;
        *integral = lowlimit - propotional_q14;
    }
    else *integral = integralx_q14;
    return output_q14;
}

uint32_t _CTRL_Get_PI_V_Controller_modified_Q(int e, int *integral, int KP, int KI, int highlimit, int lowlimit)
{
    int integralx_q14 = *integral + FMUL(KI, e, Q);
    int propotional_q14 = FMUL(KP, e, Q);
    int output_q14 = propotional_q14 + integralx_q14;
    int highlimit_q14 = FCONV(highlimit, Q_Hai, Q);
    int lowlimit_q14 = FCONV(lowlimit, Q_Hai, Q);
    if (output_q14 > highlimit_q14)
    {
        output_q14 = highlimit_q14;
        *integral = highlimit_q14 - propotional_q14;
    }
    else if (output_q14 < lowlimit_q14)
    {
        output_q14 = lowlimit_q14;
        *integral = lowlimit_q14 - propotional_q14;
    }
    else *integral = integralx_q14;
    return FCONV(output_q14, Q, Q_Hai);
}

uint32_t _CTRL_Get_PI_Controller_modified_Q(int e, int *integral, int KP, int KI, int highlimit, int lowlimit)
{
    int integralx_q9 = *integral + FMUL(KI, e, Q_Hai);
    int propotional_q9 = FMUL(KP, e, Q_Hai);
    int output_PI_q9 = propotional_q9 + integralx_q9;
    int output_PI_q0 = FCONV(output_PI_q9, Q_Hai, 0);

    /* QR controller IQMath */
    //Input data
    static int f_u1_q0 = 0, f_u2_q0 = 0;

    //output data
    static int f_o1_q0 = 0, f_o2_q0 = 0;
    static int f_Output_q12 = 0;
    static int Output_QR_q9 = 0;


    //Processing
    f_Output_q12 = _FMULI(f_v_d_w_q12, output_PI_q0) + _FMULI(f_v1_d_w_q12, f_u1_q0) + _FMULI(f_v2_d_w_q12, f_u2_q0) - _FMULI(f_w1_d_w_q12, f_o1_q0) - _FMULI(f_w2_d_w_q12, f_o2_q0);

    f_u2_q0 = f_u1_q0;
    f_u1_q0 = output_PI_q0;
    f_o2_q0 = f_o1_q0;
    f_o1_q0 = FCONV(f_Output_q12, QN, 0);

    Output_QR_q9 = FCONV(f_Output_q12, QN, Q_Hai);

    //Khi chua co QR
    //Anti wind-up
    if (output_PI_q9 > highlimit)
    {
        output_PI_q9 = highlimit;
        *integral = highlimit - propotional_q9;
    }
    else if (output_PI_q9 < lowlimit){
        output_PI_q9 = lowlimit;
        *integral = lowlimit - propotional_q9;
    }
    else *integral = integralx_q9;
    return output_PI_q9;

    //Anti wind-up
//    if (Output_QR_q9 > highlimit)
//    {
//        Output_QR_q9 = highlimit;
//        *integral = highlimit - propotional_q9;
//    }
//    else if (Output_QR_q9 < lowlimit){
//        Output_QR_q9 = lowlimit;
//        *integral = lowlimit - propotional_q9;
//    }
//    else *integral = integralx_q9;

//    return Output_QR_q9;
}


void _CTRL_Reset_Dual_Controller(void){
    const uint32_t VBULK_q14    = _TO_FIX(VBULK, Q);
    const uint32_t IMIN_q14     = _TO_FIX(IMIN, Q);
    const uint32_t IBULK_q14    = _TO_FIX(IBULK, Q);
    const uint32_t FxMIN_q14    = _TO_FIX(FxMIN, Q);
    const uint32_t FxMAX_q14    = _TO_FIX(FxMAX, Q);
    const uint32_t DMIN_q14     = _TO_FIX(DMIN, Q);
    const uint32_t DMAX_q14     = _TO_FIX(DMAX, Q);

    ControllerParams CTRL_Params = {VBULK_q14, IMIN_q14, IBULK_q14, FxMIN_q14, FxMAX_q14, DMIN_q14, DMAX_q14, false};
//    CTRL_getVIDualLoopControlledFx(0, 0, CTRL_Params);
    _CTRL_getFxDfromVIDualLoopController(0, 0, CTRL_Params);
}

uint32_t _CTRL_getFxDfromIController_NoIQMath(float ibat, float iref){
    static float iif = 0;
    int onetime = 1;
    if (onetime){
        float Frequency = (float)(80000000/DL_Timer_getLoadValue(PWM_0_INST));
        iif = Frequency;
        onetime = 0;
    }
    float KPI = 0.0;
    float KII = 800;
    static float fx;
    /*-----------------Current Loop------------------*/
    float ei = ibat - iref;
        fx = _CTRL_Get_PI_IController_NoIQMath(ei, &iif, KPI, KII, FxMAX, FxMIN);

    uint32_t Period = (uint32_t) 533/fx;
    uint32_t Duty = (uint32_t)((Period)>>1);
    HAL_setPFWM(Period, Duty, 24);
    return 1;
}

uint32_t _CTRL_getFxDfromDualVIController_NoIQMath(float vbat, float ibat){
    /*-----------------Voltage Loop------------------*/
    static float iv = 0.0;
    const float  KPV = 0.0;
    const float  KIVxTZ = 0.005;
    float ev = VBULK - vbat;
    float iref= _CTRL_Get_PI_IController_NoIQMath(ev, &iv, KPV, KIVxTZ, IBULK, IMIN);

    /*-----------------Current Loop------------------*/
    static float iif = 0;
    int onetime = 1;
    if (onetime){
        float Frequency = (float)(80000000/DL_Timer_getLoadValue(PWM_0_INST));
        iif = Frequency;
        onetime = 0;
    }
    float KPI = 0.0;
    float KIIxTz = 200;
    static float fx;
    /*-----------------Current Loop------------------*/
    float ei = ibat - iref;
        fx = _CTRL_Get_PI_IController_NoIQMath(ei, &iif, KPI, KIIxTz, FxMAX, FxMIN);

    uint32_t Period = (uint32_t) 533/fx;
    uint32_t Duty = (uint32_t)((Period)>>1);
    HAL_setPFWM(Period, Duty, 24);
    return 1;
}

uint32_t _CTRL_Get_PI_IController_NoIQMath(float e, float *integral, float KP, float KI, float highlimit, float lowlimit){
    float integralx = *integral + KI*e;
    float propotional = KP*e;
    float output = propotional + integralx;
    if (output>highlimit){
        output = highlimit;
        *integral = highlimit - propotional;
    }
    else if (output<lowlimit){
        output = lowlimit;
        *integral = lowlimit - propotional;
    }
    else *integral = integralx;
    return output;
}
