#ifndef DRV_BOTLAYER_H_
#define DRV_BOTLAYER_H_

#include "ti_msp_dl_config.h"
#include "GlobalDefinitions.h"


//*****************************************************************************
//
// Define function
//
//*****************************************************************************
#define _START_PWM()   PWM_0_INST->COUNTERREGS.CTRCTL |= (GPTIMER_CTRCTL_EN_ENABLED)
#define _STOP_PWM()    PWM_0_INST->COUNTERREGS.CTRCTL &= ~(GPTIMER_CTRCTL_EN_ENABLED)
#define _PWM_STT()     ((PWM_0_INST->COUNTERREGS.CTRCTL & GPTIMER_CTRCTL_EN_MASK) == GPTIMER_CTRCTL_EN_ENABLED)       //DL_Timer_isRunning(PWM_0_INST)

#define IS_OFP      (!!(ISRTIMER_INST->CPU_INT.RIS & DL_TIMERA_INTERRUPT_OVERFLOW_EVENT))

#define _OCP_CLR()     PWM_0_INST->CPU_INT.ICLR |= GPTIMER_CPU_INT_ICLR_F_CLR
#define _IS_OCP()      (PWM_0_INST->CPU_INT.RIS & GPTIMER_CPU_INT_RIS_F_MASK)
#define _FAN_ON()          FAN_SIGNAL_PORT->DOUTSET31_0 = FAN_SIGNAL_FAN_PIN
#define _FAN_OFF()         FAN_SIGNAL_PORT->DOUTCLR31_0 = FAN_SIGNAL_FAN_PIN
#define _LLC_RELAY_ON()    RELAY_SIGNALs_PORT->DOUTSET31_0 = RELAY_SIGNALs_LLC_RELAY_PIN
#define _LLC_RELAY_OFF()   RELAY_SIGNALs_PORT->DOUTCLR31_0 = RELAY_SIGNALs_LLC_RELAY_PIN
#define _LLC_RELAY_STT()   (RELAY_SIGNALs_PORT->DOUT31_0 & RELAY_SIGNALs_LLC_RELAY_PIN)
#define _PFC_RELAY_ON()    RELAY_SIGNALs_PORT->DOUTSET31_0 = RELAY_SIGNALs_PFC_RELAY_PIN
#define _PFC_RELAY_OFF()   RELAY_SIGNALs_PORT->DOUTCLR31_0 = RELAY_SIGNALs_PFC_RELAY_PIN
#define _PFC_RELAY_STT()   (RELAY_SIGNALs_PORT->DOUT31_0 & RELAY_SIGNALs_PFC_RELAY_PIN)
#define FCLK               80e6 //Hz
#define _LED1_ON()         LED_SIGNALs_PORT->DOUTSET31_0 = LED_SIGNALs_LED1_PIN
#define _LED1_OFF()        LED_SIGNALs_PORT->DOUTCLR31_0 = LED_SIGNALs_LED1_PIN
#define _LED1_TOGGLE()     LED_SIGNALs_PORT->DOUTTGL31_0 = LED_SIGNALs_LED1_PIN
#define _LED2_ON()         LED_SIGNALs_PORT->DOUTSET31_0 = LED_SIGNALs_LED2_PIN
#define _LED2_OFF()        LED_SIGNALs_PORT->DOUTCLR31_0 = LED_SIGNALs_LED2_PIN
#define _LED2_TOGGLE()     LED_SIGNALs_PORT->DOUTTGL31_0 = LED_SIGNALs_LED2_PIN
#define _LED3_ON()         LED_SIGNALs_PORT->DOUTSET31_0 = LED_SIGNALs_LED3_PIN
#define _LED3_OFF()        LED_SIGNALs_PORT->DOUTCLR31_0 = LED_SIGNALs_LED3_PIN
#define _LED3_TOGGLE()     LED_SIGNALs_PORT->DOUTTGL31_0 = LED_SIGNALs_LED3_PIN
#define _LED4_ON()         LED_SIGNALs_PORT->DOUTSET31_0 = LED_SIGNALs_LED4_PIN
#define _LED4_OFF()        LED_SIGNALs_PORT->DOUTCLR31_0 = LED_SIGNALs_LED4_PIN
#define _LED4_TOGGLE()     LED_SIGNALs_PORT->DOUTTGL31_0 = LED_SIGNALs_LED4_PIN

//*****************************************************************************
//
// ADC Gain
//
//*****************************************************************************
#define GAIN_VBAT   0.0275f
#define GAIN_VO     0.0275f
#define GAIN_IO     1.612e-3f
#define GAIN_TEMP   0.04f

typedef enum
{
  FUNCTION_OK       = 0x20,
  FUNCTION_ERROR    = 0x21,
  FUNCTION_BUSY     = 0x22,
  FUNCTION_TIMEOUT  = 0x23U
} FUNCTION_StatusTypeDef;

typedef enum
{
  CONTROLLER_SET    = 0x10,
  CONTROLLER_RESET  = 0x11,
  CONTROLLER_ERROR  = 0x12,
  CONTROLLER_BYPASS = 0x13
} CONTROLLER_StatusTypeDef;

void HAL_readADC(uint16_t *vo, uint16_t *vbat, uint16_t *ibat, uint16_t *temp);
void HAL_setPFM(uint32_t period, uint16_t duty, uint16_t deadtime);
void HAL_setPFWM(uint32_t period, uint16_t duty, uint16_t deadtime);
void HAL_SoftStart(uint32_t Period, uint16_t Duty, uint16_t Deadtime);
void HAL_transmitUARTMessage(char *UART_buffer, uint16_t UART_buffer_size);
void HAL_initSystem();
void HAL_setLEDsignals(uint8_t LED1_STT, uint8_t LED2_STT, uint8_t LED3_STT, uint8_t LED4_STT);
void OPNLP_SetOpenLoopOutputVolt(float desiredVout, float Vout, uint16_t Fixed_Deadtime);

#endif /* DRV_BOTLAYER_H_ */
