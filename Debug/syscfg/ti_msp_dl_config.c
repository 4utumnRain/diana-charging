/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gPWM_0Backup;
DL_TimerG_backupConfig gFANPWMBackup;
DL_TimerG_backupConfig gMACHINECYCLETIMERBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_0_init();
    SYSCFG_DL_FANPWM_init();
    SYSCFG_DL_ISRTIMER_init();
    SYSCFG_DL_MACHINECYCLETIMER_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_ADC12_0_init();
    SYSCFG_DL_ADC12_1_init();
    SYSCFG_DL_COMP_0_init();
    SYSCFG_DL_DMA_init();
    /* Ensure backup structures have no valid state */
	gPWM_0Backup.backupRdy 	= false;
	gFANPWMBackup.backupRdy 	= false;
	gMACHINECYCLETIMERBackup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(PWM_0_INST, &gPWM_0Backup);
	retStatus &= DL_TimerG_saveConfiguration(FANPWM_INST, &gFANPWMBackup);
	retStatus &= DL_TimerG_saveConfiguration(MACHINECYCLETIMER_INST, &gMACHINECYCLETIMERBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(PWM_0_INST, &gPWM_0Backup, false);
	retStatus &= DL_TimerG_restoreConfiguration(FANPWM_INST, &gFANPWMBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(MACHINECYCLETIMER_INST, &gMACHINECYCLETIMERBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_TimerA_reset(PWM_0_INST);
    DL_TimerG_reset(FANPWM_INST);
    DL_TimerG_reset(ISRTIMER_INST);
    DL_TimerG_reset(MACHINECYCLETIMER_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_ADC12_reset(ADC12_0_INST);
    DL_ADC12_reset(ADC12_1_INST);
    DL_COMP_reset(COMP_0_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_TimerA_enablePower(PWM_0_INST);
    DL_TimerG_enablePower(FANPWM_INST);
    DL_TimerG_enablePower(ISRTIMER_INST);
    DL_TimerG_enablePower(MACHINECYCLETIMER_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_ADC12_enablePower(ADC12_0_INST);
    DL_ADC12_enablePower(ADC12_1_INST);
    DL_COMP_enablePower(COMP_0_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C1_IOMUX,GPIO_PWM_0_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_0_C1_PORT, GPIO_PWM_0_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C1_CMPL_IOMUX,GPIO_PWM_0_C1_CMPL_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_0_C1_CMPL_PORT, GPIO_PWM_0_C1_CMPL_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_FANPWM_C0_IOMUX,GPIO_FANPWM_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_FANPWM_C0_PORT, GPIO_FANPWM_C0_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(RELAY_SIGNALs_LLC_RELAY_IOMUX);

    DL_GPIO_initDigitalOutput(FAN_SIGNAL_FAN_IOMUX);

    DL_GPIO_initDigitalInputFeatures(INPUT_SIGNALs_VIN_DETECTION_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(LED_SIGNALs_LED1_IOMUX);

    DL_GPIO_initDigitalOutput(LED_SIGNALs_LED2_IOMUX);

    DL_GPIO_initDigitalOutput(LED_SIGNALs_LED3_IOMUX);

    DL_GPIO_initDigitalOutput(LED_SIGNALs_LED4_IOMUX);

    DL_GPIO_clearPins(GPIOA, RELAY_SIGNALs_LLC_RELAY_PIN |
		LED_SIGNALs_LED1_PIN |
		LED_SIGNALs_LED2_PIN |
		LED_SIGNALs_LED3_PIN |
		LED_SIGNALs_LED4_PIN);
    DL_GPIO_setPins(GPIOA, FAN_SIGNAL_FAN_PIN);
    DL_GPIO_enableOutput(GPIOA, RELAY_SIGNALs_LLC_RELAY_PIN |
		FAN_SIGNAL_FAN_PIN |
		LED_SIGNALs_LED1_PIN |
		LED_SIGNALs_LED2_PIN |
		LED_SIGNALs_LED3_PIN |
		LED_SIGNALs_LED4_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_16_32_MHZ,
	.rDivClk2x              = 0,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_SYSOSC,
	.qDiv                   = 9,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_2,
	
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    /* Set default configuration */
    DL_SYSCTL_disableHFXT();
    DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
	
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_1);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);

}


/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gPWM_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gPWM_0Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 160,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_0_init(void) {

    DL_TimerA_setClockConfig(
        PWM_0_INST, (DL_TimerA_ClockConfig *) &gPWM_0ClockConfig);

    DL_TimerA_initPWMMode(
        PWM_0_INST, (DL_TimerA_PWMConfig *) &gPWM_0Config);

    DL_TimerA_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_DEAD_BAND,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_ZERO_EVT, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_0_INST, 80, DL_TIMER_CC_1_INDEX);

    DL_TimerA_setDeadBand(PWM_0_INST, 32, 32, DL_TIMER_DEAD_BAND_MODE_0);
    DL_TimerA_enableClock(PWM_0_INST);


    
    DL_TimerA_setCCPDirection(PWM_0_INST , DL_TIMER_CC1_OUTPUT );
    DL_TimerA_enableShadowFeatures(PWM_0_INST);


    DL_TimerA_setFaultSourceConfig(PWM_0_INST, (DL_TIMERA_FAULT_SOURCE_COMP0_SENSE_HIGH));
    DL_TimerA_setFaultConfig(PWM_0_INST, DL_TIMERA_FAULT_CONFIG_TFIM_DISABLED
		 | DL_TIMERA_FAULT_CONFIG_FL_LATCH_SW_CLR
		 | DL_TIMERA_FAULT_CONFIG_FI_DEPENDENT
		 | DL_TIMERA_FAULT_CONFIG_FIEN_ENABLED);
    DL_TimerA_setFaultInputFilterConfig(PWM_0_INST,
        DL_TIMERA_FAULT_FILTER_FILTERED,
        DL_TIMERA_FAULT_FILTER_CPV_CONSEC_PER,
        DL_TIMERA_FAULT_FILTER_FP_PER_3);
    DL_TimerA_configFaultOutputAction(PWM_0_INST,
        DL_TIMERA_FAULT_ENTRY_CCP_LOW,
        DL_TIMERA_FAULT_EXIT_CCP_LOW,
        DL_TIMER_CC_1_INDEX);
    DL_TimerA_configFaultCounter(PWM_0_INST,
        DL_TIMERA_FAULT_ENTRY_CTR_SUSP_COUNT, DL_TIMERA_FAULT_EXIT_CTR_CVAE_ACTION);
    DL_TimerA_enableFaultInput(PWM_0_INST);
    DL_TimerA_disableClockFaultDetection(PWM_0_INST);
}
/*
 * Timer clock configuration to be sourced by  / 3 (26666666.666666668 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   26666666.666666668 Hz = 26666666.666666668 Hz / (3 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gFANPWMClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_3,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gFANPWMConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_FANPWM_init(void) {

    DL_TimerG_setClockConfig(
        FANPWM_INST, (DL_TimerG_ClockConfig *) &gFANPWMClockConfig);

    DL_TimerG_initPWMMode(
        FANPWM_INST, (DL_TimerG_PWMConfig *) &gFANPWMConfig);

    DL_TimerG_setCaptureCompareOutCtl(FANPWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(FANPWM_INST, DL_TIMER_CC_UPDATE_METHOD_ZERO_EVT, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(FANPWM_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(FANPWM_INST);


    
    DL_TimerG_setCCPDirection(FANPWM_INST , DL_TIMER_CC0_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 10000000 Hz / (8 * (9 + 1))
 */
static const DL_TimerG_ClockConfig gISRTIMERClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 9U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * ISRTIMER_INST_LOAD_VALUE = (50 us * 1000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gISRTIMERTimerConfig = {
    .period     = ISRTIMER_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_ISRTIMER_init(void) {

    DL_TimerG_setClockConfig(ISRTIMER_INST,
        (DL_TimerG_ClockConfig *) &gISRTIMERClockConfig);

    DL_TimerG_initTimerMode(ISRTIMER_INST,
        (DL_TimerG_TimerConfig *) &gISRTIMERTimerConfig);
    DL_TimerG_enableInterrupt(ISRTIMER_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(ISRTIMER_INST_INT_IRQN, 0);
    DL_TimerG_enableClock(ISRTIMER_INST);


    DL_TimerG_enableEvent(ISRTIMER_INST, DL_TIMERG_EVENT_ROUTE_1, (DL_TIMERG_EVENT_ZERO_EVENT));

    DL_TimerG_setPublisherChanID(ISRTIMER_INST, DL_TIMERG_PUBLISHER_INDEX_0, ISRTIMER_INST_PUB_0_CH);

    DL_TimerG_enableEvent(ISRTIMER_INST, DL_TIMERG_EVENT_ROUTE_2, (DL_TIMERG_EVENT_ZERO_EVENT));

    DL_TimerG_setPublisherChanID(ISRTIMER_INST, DL_TIMERG_PUBLISHER_INDEX_1, ISRTIMER_INST_PUB_1_CH);


}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gMACHINECYCLETIMERClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * MACHINECYCLETIMER_INST_LOAD_VALUE = (200 us * 80000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gMACHINECYCLETIMERTimerConfig = {
    .period     = MACHINECYCLETIMER_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_MACHINECYCLETIMER_init(void) {

    DL_TimerG_setClockConfig(MACHINECYCLETIMER_INST,
        (DL_TimerG_ClockConfig *) &gMACHINECYCLETIMERClockConfig);

    DL_TimerG_initTimerMode(MACHINECYCLETIMER_INST,
        (DL_TimerG_TimerConfig *) &gMACHINECYCLETIMERTimerConfig);
    DL_TimerG_enableClock(MACHINECYCLETIMER_INST);





}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.1
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_80_MHZ_9600_BAUD, UART_0_FBRD_80_MHZ_9600_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);

    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(UART_0_INST);
    /* Configure FIFOs */
    DL_UART_Main_enableFIFOs(UART_0_INST);
    DL_UART_Main_setRXFIFOThreshold(UART_0_INST, DL_UART_RX_FIFO_LEVEL_ONE_ENTRY);
    DL_UART_Main_setTXFIFOThreshold(UART_0_INST, DL_UART_TX_FIFO_LEVEL_ONE_ENTRY);

    DL_UART_Main_enable(UART_0_INST);
}

/* ADC12_0 Initialization */
static const DL_ADC12_ClockConfig gADC12_0ClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_SYSOSC,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC12_0_init(void)
{
    DL_ADC12_setClockConfig(ADC12_0_INST, (DL_ADC12_ClockConfig *) &gADC12_0ClockConfig);

    DL_ADC12_initSeqSample(ADC12_0_INST,
        DL_ADC12_REPEAT_MODE_ENABLED, DL_ADC12_SAMPLING_SOURCE_AUTO, DL_ADC12_TRIG_SRC_EVENT,
        DL_ADC12_SEQ_START_ADDR_01, DL_ADC12_SEQ_END_ADDR_03, DL_ADC12_SAMP_CONV_RES_12_BIT,
        DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED);
    DL_ADC12_configConversionMem(ADC12_0_INST, ADC12_0_ADCMEM_TEMP,
        DL_ADC12_INPUT_CHAN_1, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_ENABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_configConversionMem(ADC12_0_INST, ADC12_0_ADCMEM_VBAT,
        DL_ADC12_INPUT_CHAN_7, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_ENABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_configConversionMem(ADC12_0_INST, ADC12_0_ADCMEM_IBAT,
        DL_ADC12_INPUT_CHAN_8, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_ENABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_configHwAverage(ADC12_0_INST,DL_ADC12_HW_AVG_NUM_ACC_64,DL_ADC12_HW_AVG_DEN_DIV_BY_64);
    DL_ADC12_setSubscriberChanID(ADC12_0_INST,ADC12_0_INST_SUB_CH);
    DL_ADC12_enableConversions(ADC12_0_INST);
}
/* ADC12_1 Initialization */
static const DL_ADC12_ClockConfig gADC12_1ClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_SYSOSC,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC12_1_init(void)
{
    DL_ADC12_setClockConfig(ADC12_1_INST, (DL_ADC12_ClockConfig *) &gADC12_1ClockConfig);
    DL_ADC12_initSingleSample(ADC12_1_INST,
        DL_ADC12_REPEAT_MODE_ENABLED, DL_ADC12_SAMPLING_SOURCE_AUTO, DL_ADC12_TRIG_SRC_EVENT,
        DL_ADC12_SAMP_CONV_RES_12_BIT, DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED);
    DL_ADC12_configConversionMem(ADC12_1_INST, ADC12_1_ADCMEM_VO,
        DL_ADC12_INPUT_CHAN_3, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_ENABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_configHwAverage(ADC12_1_INST,DL_ADC12_HW_AVG_NUM_ACC_64,DL_ADC12_HW_AVG_DEN_DIV_BY_64);
    DL_ADC12_setSubscriberChanID(ADC12_1_INST,ADC12_1_INST_SUB_CH);
    DL_ADC12_enableConversions(ADC12_1_INST);
}

/* COMP_0 Initialization */
static const DL_COMP_Config gCOMP_0Config = {
    .channelEnable = DL_COMP_ENABLE_CHANNEL_POS,
    .mode          = DL_COMP_MODE_FAST,
    .negChannel    = DL_COMP_IMSEL_CHANNEL_0,
    .posChannel    = DL_COMP_IPSEL_CHANNEL_0,
    .hysteresis    = DL_COMP_HYSTERESIS_30,
    .polarity      = DL_COMP_POLARITY_NON_INV
};
static const DL_COMP_RefVoltageConfig gCOMP_0VRefConfig = {
    .mode           = DL_COMP_REF_MODE_STATIC,
    .source         = DL_COMP_REF_SOURCE_VDDA_DAC,
    .terminalSelect = DL_COMP_REF_TERMINAL_SELECT_NEG,
    .controlSelect  = DL_COMP_DAC_CONTROL_SW,
    .inputSelect    = DL_COMP_DAC_INPUT_DACCODE0
};

SYSCONFIG_WEAK void SYSCFG_DL_COMP_0_init(void)
{
    DL_COMP_init(COMP_0_INST, (DL_COMP_Config *) &gCOMP_0Config);
    DL_COMP_refVoltageInit(COMP_0_INST, (DL_COMP_RefVoltageConfig *) &gCOMP_0VRefConfig);
    DL_COMP_setDACCode0(COMP_0_INST, COMP_0_DACCODE0);

    DL_COMP_enable(COMP_0_INST);

}


static const DL_DMA_Config gDMA_CH_TXConfig = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = UART_0_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH_TX_init(void)
{
    DL_DMA_initChannel(DMA, DMA_CH_TX_CHAN_ID , (DL_DMA_Config *) &gDMA_CH_TXConfig);
}
SYSCONFIG_WEAK void SYSCFG_DL_DMA_init(void){
    SYSCFG_DL_DMA_CH_TX_init();
}


