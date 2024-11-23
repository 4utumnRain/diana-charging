/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3505

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA1
#define PWM_0_INST_IRQHandler                                   TIMA1_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                         DL_GPIO_PIN_11
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM22)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM22_PF_TIMA1_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_CMPL_PORT                                            GPIOA
#define GPIO_PWM_0_C1_CMPL_PIN                                     DL_GPIO_PIN_9
#define GPIO_PWM_0_C1_CMPL_IOMUX                                 (IOMUX_PINCM20)
#define GPIO_PWM_0_C1_CMPL_IOMUX_FUNC           IOMUX_PINCM20_PF_TIMA1_CCP1_CMPL


/* Defines for FANPWM */
#define FANPWM_INST                                                        TIMG7
#define FANPWM_INST_IRQHandler                                  TIMG7_IRQHandler
#define FANPWM_INST_INT_IRQN                                    (TIMG7_INT_IRQn)
#define FANPWM_INST_CLK_FREQ                                  26666666.666666668
/* GPIO defines for channel 0 */
#define GPIO_FANPWM_C0_PORT                                                GPIOA
#define GPIO_FANPWM_C0_PIN                                         DL_GPIO_PIN_3
#define GPIO_FANPWM_C0_IOMUX                                      (IOMUX_PINCM8)
#define GPIO_FANPWM_C0_IOMUX_FUNC                     IOMUX_PINCM8_PF_TIMG7_CCP0
#define GPIO_FANPWM_C0_IDX                                   DL_TIMER_CC_0_INDEX



/* Defines for ISRTIMER */
#define ISRTIMER_INST                                                    (TIMG0)
#define ISRTIMER_INST_IRQHandler                                TIMG0_IRQHandler
#define ISRTIMER_INST_INT_IRQN                                  (TIMG0_INT_IRQn)
#define ISRTIMER_INST_LOAD_VALUE                                           (49U)
#define ISRTIMER_INST_PUB_0_CH                                               (1)
#define ISRTIMER_INST_PUB_1_CH                                               (2)
/* Defines for MACHINECYCLETIMER */
#define MACHINECYCLETIMER_INST                                           (TIMG6)
#define MACHINECYCLETIMER_INST_IRQHandler                        TIMG6_IRQHandler
#define MACHINECYCLETIMER_INST_INT_IRQN                         (TIMG6_INT_IRQn)
#define MACHINECYCLETIMER_INST_LOAD_VALUE                                (15999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART1
#define UART_0_INST_FREQUENCY                                           80000000
#define UART_0_INST_IRQHandler                                  UART1_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_18
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM40)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM39)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM40_PF_UART1_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM39_PF_UART1_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_80_MHZ_9600_BAUD                                       (520)
#define UART_0_FBRD_80_MHZ_9600_BAUD                                        (53)





/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC1
#define ADC12_0_INST_IRQHandler                                  ADC1_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC1_INT_IRQn)
#define ADC12_0_ADCMEM_TEMP                                   DL_ADC12_MEM_IDX_1
#define ADC12_0_ADCMEM_TEMP_REF                  DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_TEMP_REF_VOLTAGE_V                                     3.3
#define ADC12_0_ADCMEM_VBAT                                   DL_ADC12_MEM_IDX_2
#define ADC12_0_ADCMEM_VBAT_REF                  DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_VBAT_REF_VOLTAGE_V                                     3.3
#define ADC12_0_ADCMEM_IBAT                                   DL_ADC12_MEM_IDX_3
#define ADC12_0_ADCMEM_IBAT_REF                  DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_IBAT_REF_VOLTAGE_V                                     3.3
#define ADC12_0_INST_SUB_CH                                                  (1)
#define GPIO_ADC12_0_C1_PORT                                               GPIOA
#define GPIO_ADC12_0_C1_PIN                                       DL_GPIO_PIN_16
#define GPIO_ADC12_0_C7_PORT                                               GPIOA
#define GPIO_ADC12_0_C7_PIN                                       DL_GPIO_PIN_21
#define GPIO_ADC12_0_C8_PORT                                               GPIOA
#define GPIO_ADC12_0_C8_PIN                                       DL_GPIO_PIN_22

/* Defines for ADC12_1 */
#define ADC12_1_INST                                                        ADC0
#define ADC12_1_INST_IRQHandler                                  ADC0_IRQHandler
#define ADC12_1_INST_INT_IRQN                                    (ADC0_INT_IRQn)
#define ADC12_1_ADCMEM_VO                                     DL_ADC12_MEM_IDX_0
#define ADC12_1_ADCMEM_VO_REF                    DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_1_ADCMEM_VO_REF_VOLTAGE_V                                      3.3
#define ADC12_1_INST_SUB_CH                                                  (2)
#define GPIO_ADC12_1_C3_PORT                                               GPIOA
#define GPIO_ADC12_1_C3_PIN                                       DL_GPIO_PIN_24



/* Defines for COMP_0 */
#define COMP_0_INST                                                        COMP0
#define COMP_0_INST_INT_IRQN                                      COMP0_INT_IRQn

/* Defines for COMP_0 DACCODE0 */
#define COMP_0_DACCODE0                                                    (255)


/* GPIO configuration for COMP_0 */
#define GPIO_COMP_0_IN0P_PORT                                            (GPIOA)
#define GPIO_COMP_0_IN0P_PIN                                    (DL_GPIO_PIN_26)
#define GPIO_COMP_0_IOMUX_IN0P                                   (IOMUX_PINCM59)
#define GPIO_COMP_0_IOMUX_IN0P_FUNC               (IOMUX_PINCM59_PF_UNCONNECTED)





/* Defines for DMA_CH_TX */
#define DMA_CH_TX_CHAN_ID                                                    (0)
#define UART_0_INST_DMA_TRIGGER                              (DMA_UART1_TX_TRIG)



/* Port definition for Pin Group RELAY_SIGNALs */
#define RELAY_SIGNALs_PORT                                               (GPIOA)

/* Defines for LLC_RELAY: GPIOA.25 with pinCMx 55 on package pin 29 */
#define RELAY_SIGNALs_LLC_RELAY_PIN                             (DL_GPIO_PIN_25)
#define RELAY_SIGNALs_LLC_RELAY_IOMUX                            (IOMUX_PINCM55)
/* Port definition for Pin Group FAN_SIGNAL */
#define FAN_SIGNAL_PORT                                                  (GPIOA)

/* Defines for FAN: GPIOA.14 with pinCMx 36 on package pin 18 */
#define FAN_SIGNAL_FAN_PIN                                      (DL_GPIO_PIN_14)
#define FAN_SIGNAL_FAN_IOMUX                                     (IOMUX_PINCM36)
/* Port definition for Pin Group INPUT_SIGNALs */
#define INPUT_SIGNALs_PORT                                               (GPIOA)

/* Defines for VIN_DETECTION: GPIOA.12 with pinCMx 34 on package pin 16 */
#define INPUT_SIGNALs_VIN_DETECTION_PIN                         (DL_GPIO_PIN_12)
#define INPUT_SIGNALs_VIN_DETECTION_IOMUX                        (IOMUX_PINCM34)
/* Port definition for Pin Group LED_SIGNALs */
#define LED_SIGNALs_PORT                                                 (GPIOA)

/* Defines for LED1: GPIOA.5 with pinCMx 10 on package pin 9 */
#define LED_SIGNALs_LED1_PIN                                     (DL_GPIO_PIN_5)
#define LED_SIGNALs_LED1_IOMUX                                   (IOMUX_PINCM10)
/* Defines for LED2: GPIOA.6 with pinCMx 11 on package pin 10 */
#define LED_SIGNALs_LED2_PIN                                     (DL_GPIO_PIN_6)
#define LED_SIGNALs_LED2_IOMUX                                   (IOMUX_PINCM11)
/* Defines for LED3: GPIOA.7 with pinCMx 14 on package pin 11 */
#define LED_SIGNALs_LED3_PIN                                     (DL_GPIO_PIN_7)
#define LED_SIGNALs_LED3_IOMUX                                   (IOMUX_PINCM14)
/* Defines for LED4: GPIOA.8 with pinCMx 19 on package pin 12 */
#define LED_SIGNALs_LED4_PIN                                     (DL_GPIO_PIN_8)
#define LED_SIGNALs_LED4_IOMUX                                   (IOMUX_PINCM19)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_FANPWM_init(void);
void SYSCFG_DL_ISRTIMER_init(void);
void SYSCFG_DL_MACHINECYCLETIMER_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_ADC12_0_init(void);
void SYSCFG_DL_ADC12_1_init(void);
void SYSCFG_DL_COMP_0_init(void);
void SYSCFG_DL_DMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
