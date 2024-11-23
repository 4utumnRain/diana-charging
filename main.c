#include "app_EbikeCharger.h"
#include "drv_BotLayer.h" //abc xyz
#include "ti_msp_dl_config.h"
#include "GlobalDefinitions.h"
#include "stdio.h"
#include "string.h"
#include "System_Recorder.h"
#include "UARTLib.h"




volatile bool gCheckUART = true;
//#define OPEN_LOOP_TEST
uint16_t Fsw = 0U;
uint16_t Tsw = 0U;
uint16_t D = 0U;
uint16_t time_measure = 0U;
uint8_t flag;
uint16_t Debug_Mode = 0U;
uint32_t cntLED = 0;
//#define OPEN_LOOP_TEST
char receiveChar;
char rxPacket[50];
uint8_t index_rxPacket = 0;

RecorderPackageTypeDef WritePackage;
RecorderPackageTypeDef ReadPackage;
Operating_Mode Print_Saved_State;
int main(void)
{
    SYSCFG_DL_init();

    //_Read_Mode_Test (WritePackage);
    ReadPackage.TxFlashDataFlag = false;
    _Recorder_Check(&ReadPackage, &Print_Saved_State);
    //ReadPackage.TxFlashDataFlag = true;

    /* Cap nhat dia chi tai thanh ghi blank */
    WritePackage.Address = ReadPackage.Address + 0x07 + 16U ;

    /* Che do hien thi loi gan nhat trong 3s dau */
    delay_cycles(32000000); //Delay 1s
    Charger_State = MODE_BATTERY_CHECK;

    /* Cho phep ghi du lieu vao bo nho */
    WritePackage.writeFlag = true;

    HAL_initSystem();
    while (1) {
             ADCbuffer[0] = DL_ADC12_getMemResult(ADC12_1_INST, ADC12_1_ADCMEM_VO);
             ADCbuffer[1] = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_VBAT);
             ADCbuffer[2] = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_IBAT);
             ADCbuffer[3] = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_TEMP);

             DL_Timer_setCaptureCompareValue(FANPWM_INST, PRFL_getTemperatureDeratingFAN(ADCbuffer[3]), DL_TIMER_CC_0_INDEX);

             Tsw = DL_Timer_getLoadValue(PWM_0_INST);
             Fsw = (uint16_t)(80e3/Tsw);
             D = (100*DL_Timer_getCaptureCompareValue(PWM_0_INST, DL_TIMER_CC_1_INDEX))/Tsw;

//             printf("Received rxPacket: %s\n", rxPacket);
                     splitArray(rxPacket, &mcuVac, &mcuTemp);
                     //printf("mcuVac = %d and mcuTemp = %d \n", mcuVac, mcuTemp);
                     index_rxPacket = 0;        //Clear index
             sprintf(txUART,"\r%5d,%d,%d,%4.1f,%4.1f,%4.1f,%4.1f,%4.1d,%4.1d,%2d,%5d,%s",
                     Global_Time/100, Fsw, D,
                     (float)ADCbuffer[0]*0.0304-2.3768, (float)ADCbuffer[1]*0.0274+0.126,
                     (float)ADCbuffer[2]*0.0135+0.0288, (float)ADCbuffer[3],
                     mcuVac, mcuTemp,
                     Charger_State,
                     WatchDog_Time/100, _CHRGR_Get_Charger_State(Charger_State));
             HAL_transmitUARTMessage(txUART, strlen(txUART));
        }

        //UART Communication Tasks
        //HAL_receiveUARTMessage(rxUART, 20);
        //HAL_transmitUARTMessage(rxUART, strlen(rxUART));
}

void ISRTIMER_INST_IRQHandler(void)
{
    // Read ADC for Controller and Protection
    uint16_t voADC     = DL_ADC12_getMemResult(ADC12_1_INST, ADC12_1_ADCMEM_VO)   -78;
    uint16_t vbatADC   = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_VBAT) +5;
    uint16_t ibatADC   = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_IBAT) +2;
    uint16_t tempADC   = 0*DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_TEMP);

    float vo    = (float)voADC*0.0304-2.3768;
    float vbat  = (float)vbatADC*0.0274+0.126;
    float ibat  = (float)ibatADC*0.0135+0.0288;
    float temp  = 0.0;
    CHRGR_manageOperationProtectings(&Charger_State, vbat, vo, ibat, temp);
    #ifdef OPEN_LOOP_TEST
        static uint16_t first_time = 1;
        static uint16_t cnt = 0;
        if(first_time){
            Charger_State = MODE_OPEN_LOOP;
            _LLC_RELAY_ON();
            HAL_setPFM(160, 50, 48);
            _START_PWM();
            first_time = 0;
        }
        if(cnt>=20000){
            //OPNLP_SetOpenLoopOutputVolt(84.0, vo, 24);    // Frequency = 250 kHz, Deadtime = 300ns;
            OPNLP_SetOpenLoopOutputVolt(84.0, 50.0, 24);
        }
        else cnt++;
        //if (_IS_PROTECTING())   _CHRGR_Execute_System_Stop();
    #else
        //Start Executing Charger Operation States
        CHRGR_manageOperationStates(&Charger_State, vbatADC, voADC, ibatADC, tempADC);
        //End Executing Charger Operation States
    #endif

        //Clear Zero Event//
        ISRTIMER_INST->CPU_INT.ICLR = 1;
        time_measure = MACHINECYCLETIMER_INST->COUNTERREGS.CTR & GPTIMER_CTR_CCTR_MASK;
}

void UART_0_INST_IRQHandler(void)
{
    if (DL_UART_Main_getPendingInterrupt(UART_0_INST) == DL_UART_MAIN_IIDX_RX)
    {

        receiveChar = DL_UART_Main_receiveData(UART_0_INST);
        rxPacket[index_rxPacket] = receiveChar;
        index_rxPacket++;
    }
    rxPacket[index_rxPacket] = '\0';
    DL_UART_Main_clearInterruptStatus(UART_0_INST, DL_UART_MAIN_INTERRUPT_RX);
}
