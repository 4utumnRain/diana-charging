/*
 * MidLayer.c
 *
 *  Created on: 22 Dec 2023
 *      Author: DELL
 */

#include <drv_BotLayer.h>

//*****************************************************************************
//
// Read ADC and convert to real value
//
//*****************************************************************************
void HAL_readADC(uint16_t *vo, uint16_t *vbat, uint16_t *ibat, uint16_t *temp){
//    *vo     = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_VO);
//    *vbat   = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_VBAT);
//    *ibat   = DL_ADC12_getMemResult(ADC12_1_INST, ADC12_1_ADCMEM_IBAT);
    *temp   = 0;//DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_TEMP);
}

//*****************************************************************************
//
// Update Period, Duty and DeadTime for EPWM
//
//*****************************************************************************

void OPNLP_SetOpenLoopOutputVolt(float desiredVout, float Vout, uint16_t Fixed_Deadtime)
{
    static uint16_t instantPeriod = 133; //Maximum freq = 500kHz
    const uint16_t EndPeriod = 533; // Minimum freq = 250 kHz

    static uint16_t instantDeadtimeCntValue = 48; //600ns
    const uint16_t endDeadtimeCntValue = (uint16_t)(Fixed_Deadtime);     // Do Tclk = 120 M --> DEADTIME = T_Dead/T_CLK = T_DEAD*12/100 (ns)


    if( ISR_Delay_us(10000, 20))        // Thoi gian ISR ung voi 50kHz nen 1 lan ISR la 20us Suy ra de dat duoc 20000us can 20000/20 lan cnt ++
    {
        if (instantPeriod < EndPeriod && Vout < desiredVout)
        {
            instantPeriod++;

            if (instantDeadtimeCntValue > endDeadtimeCntValue) instantDeadtimeCntValue--;
            HAL_setPFM(instantPeriod, 50, instantDeadtimeCntValue);
        }
   }
}

void HAL_setPFM(uint32_t period, uint16_t duty, uint16_t deadtime){
    uint16_t CaptureCompareValue;
    if (duty!=50)   {CaptureCompareValue = period*duty/100;}
    else            {CaptureCompareValue = period>>1;}
    PWM_0_INST->COUNTERREGS.LOAD = period;
    DL_Timer_setCaptureCompareValue(PWM_0_INST, CaptureCompareValue, DL_TIMER_CC_1_INDEX);
    PWM_0_INST->COUNTERREGS.DBCTL =
            (((uint32_t) deadtime << GPTIMER_DBCTL_FALLDELAY_OFS) |
                (uint32_t) deadtime | 0);
}

void HAL_setPFWM(uint32_t period, uint16_t duty, uint16_t deadtime){
    uint16_t CaptureCompareValue = duty;
    PWM_0_INST->COUNTERREGS.LOAD = period;
    DL_Timer_setCaptureCompareValue(PWM_0_INST, CaptureCompareValue, DL_TIMER_CC_1_INDEX);
    PWM_0_INST->COUNTERREGS.DBCTL =
            (((uint32_t) deadtime << GPTIMER_DBCTL_FALLDELAY_OFS) |
                (uint32_t) deadtime | 0);
}

void HAL_SoftStart(uint32_t Period, uint16_t Duty, uint16_t Deadtime)
{
    static uint16_t instantPeriod = 160;            //Maximum freq = 500kHz
    const uint16_t EndPeriod = 800;                 // Minimum freq = 250 kHz

    static uint16_t instantDeadtimeCntValue = 48;   //600ns
    const uint16_t endDeadtimeCntValue = (uint16_t)(Deadtime);
    if( ISR_Delay_us(10000, 20))
    {
        if (instantPeriod < EndPeriod)
        {
            instantPeriod++;
            if (instantDeadtimeCntValue > endDeadtimeCntValue) instantDeadtimeCntValue--;
            HAL_setPFM(instantPeriod, Duty, instantDeadtimeCntValue);
        }
   }
}

//*****************************************************************************
//
// Transmit data through UART
//
//*****************************************************************************

void HAL_transmitUARTMessage(char *UART_buffer, uint16_t UART_buffer_size){
    DL_DMA_setSrcAddr(DMA, DMA_CH_TX_CHAN_ID, (uint32_t) &UART_buffer[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH_TX_CHAN_ID, (uint32_t)(&UART_0_INST->TXDATA));
    DL_DMA_setTransferSize(
        DMA, DMA_CH_TX_CHAN_ID, UART_buffer_size);
    DL_DMA_enableChannel(DMA, DMA_CH_TX_CHAN_ID);
}

//void HAL_receiveUARTMessage(char *UART_buffer, uint16_t UART_buffer_size){
//    DL_DMA_setSrcAddr(DMA, DMA_CH_RX_CHAN_ID,  (uint32_t)(&UART_0_INST->RXDATA));
//    DL_DMA_setDestAddr(DMA, DMA_CH_RX_CHAN_ID, (uint32_t) &UART_buffer[0]);
//    DL_DMA_setTransferSize(
//        DMA, DMA_CH_RX_CHAN_ID, UART_buffer_size);
//    DL_DMA_enableChannel(DMA, DMA_CH_RX_CHAN_ID);
//}

//*****************************************************************************
//
// Transmit data through UART
//
//*****************************************************************************

void HAL_initSystem()
{
    delay_cycles(240000000); //Delay 2.5s
    //_PFC_RELAY_ON();
//    _FAN_ON();
    DL_Timer_setLoadValue(ISRTIMER_INST, Tz/(1e-6));
    DL_TimerG_startCounter(ISRTIMER_INST);

    DL_COMP_setDACCode0(COMP_0_INST, 255);//194
    DL_COMP_enable(COMP_0_INST);

 //   Operating_Mode Charger_State = MODE_BATTERY_CHECK;
    _OCP_CLR();

//    DL_GPIO_setPins(GPIO0_PORT, GPIO0_PIN0_PIN);
    NVIC_EnableIRQ(ISRTIMER_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

}

void HAL_setLEDsignals(uint8_t LED1, uint8_t LED2, uint8_t LED3, uint8_t LED4){
    switch (LED1) {
        case 2: _LED1_TOGGLE();    break;
        case 1: _LED1_ON();        break;
        case 0: _LED1_OFF();       break;
        default:_LED1_OFF();       break;
    }
    switch (LED2) {
        case 2: _LED2_TOGGLE();    break;
        case 1: _LED2_ON();        break;
        case 0: _LED2_OFF();       break;
        default:_LED2_OFF();       break;
    }
    switch (LED3) {
        case 2: _LED3_TOGGLE();    break;
        case 1: _LED3_ON();        break;
        case 0: _LED3_OFF();       break;
        default:_LED3_OFF();       break;
    }
    switch (LED4) {
        case 2: _LED4_TOGGLE();    break;
        case 1: _LED4_ON();        break;
        case 0: _LED4_OFF();       break;
        default:_LED4_OFF();       break;
    }
}



