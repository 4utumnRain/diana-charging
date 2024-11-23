/*
 * System_Recorder.h
 *
 *  Created on: Mar 28, 2024
 *      Author: ADMIN
 */

#ifndef SYSTEM_RECORDER_H_
#define SYSTEM_RECORDER_H_

#include "ti_msp_dl_config.h"
#include "drv_BotLayer.h"
#include "GlobalDefinitions.h"
#include "app_EbikeCharger.h"
#include "stdio.h"
#include "string.h"


/* Codes to understand where error occured */
#define NO_ERROR 0
#define ERROR_ERASE 1
#define ERROR_WRITE_8_BIT 2
#define ERROR_READ_8_BIT 3
#define ERROR_WRITE_16_BIT 4
#define ERROR_READ_16_BIT 5
#define ERROR_WRITE_32_BIT 6
#define ERROR_READ_32_BIT 7
#define ERROR_WRITE_64_BIT 8
#define ERROR_READ_64_BIT 9
#define ERROR_EXPECTED_FAIL 10
#define ERROR_UNEXPECTED 11
#define ERROR_WRITE_64_OVERRIDE 12
#define ERROR_READ_64_OVERRIDE 13
#define ERROR_EXPECTED_FAIL_OVERRIDE 14

/*
 * Read Addr = Write Addr - 0x07
 * Sector 1: Write Addr: 0x7C00 -> 0x7FFF   |   Each sector can save 128 128-bit-package
 * Sector 2: Write Addr: 0x7800 -> 0x7BFF
 * Sector 3: Write Addr: 0x7400 -> 0x77FF
 * Sector 4: Write Addr: 0x7000 -> 0x73FF
 * Sector 5: Write Addr: 0x6C00 -> 0x6FFF
 * Sector 6: Write Addr: 0x6800 -> 0x6BFF
 * Sector 7: Write Addr: 0x6400 -> 0x67FF
 * Sector 8: Write Addr: 0x6000 -> 0x63FF
 */
#define SECTOR_ADDRESS_SIZE       (0x3FF)
#define SYSTEM_WRITE_BASE_ADDRESS (0x7FFF)
#define SYSTEM_READ_BASE_ADDRESS  (CHRG_DATA_WRITE_BASE_ADDRESS - 0x07)
#define SYSTEM_WRITE_STOP_ADDRESS (0x7C00)
#define SYSTEM_READ_STOP_ADDRESS (SYSTEM_WRITE_STOP_ADDRESS - 0x07)

#define CHRG_DATA_WRITE_BASE_ADDRESS (0x7BFF)
#define CHRG_DATA_READ_BASE_ADDRESS  (CHRG_DATA_WRITE_BASE_ADDRESS - 0x07)
#define CHRG_DATA_WRITE_STOP_ADDRESS  (0x6000)
#define CHRG_DATA_READ_STOP_ADDRESS   (CHRG_DATA_WRITE_STOP_ADDRESS - 0x07)
#define RECORD_PACKAGE_SIZE 128 //bits
#define _READ_DATA_FROM(Address) *(uint64_t*)(Address);

#define TYPE_OF_PACKAGE_NORMAL_MODE              0x00
#define TYPE_OF_PACKAGE_ERROR_MODE               0x01
#define TYPE_OF_PACKAGE_PROTECTION_MODE          0x02
#define TYPE_OF_PACKAGE_TESTING_MODE             0xFF

#define MEMORY_INDICATE_MAX_TIME                 15e4
#define PREVIOUS_SAVED_MODE_READ                 2
#define IsBOR          ((lastStateOfCharger == tagPreCharging || lastStateOfCharger == tagBulkCharging) && (stateOfCharger == tagOVP))
typedef struct  {  //Write to flash packaging
  uint32_t Address;
  uint8_t typeOfPackage;            // 2-bit; 0b00: Error Type, 0b01: Normal Operation Type, 0b10: Protection Type
  uint16_t initialVbat;             // 12-bit; Initial ADC value of battery voltage
  uint16_t lastVbat;                // 12-bit; last battery voltage ADC value before PWM off
  uint16_t lastIbat;
  uint16_t lastTemperature;
  uint16_t maxTemperature;
  uint16_t prechargeTime;           // 15-bit; Amount of time for pre-charge mode
  uint16_t chargeTime;                  // 15-bit; Amount of time for constant-current mode
  uint16_t internalResistor;        // 14-bit; Value of battery internal resistor before charging
  uint64_t stateOfCharge;           // 28-bit; Value of state of charge based on coulomb counting
  uint32_t protectionMode;                //
  uint32_t errorMode;               //
  bool writeFlag;
  bool TxFlashDataFlag;

}RecorderPackageTypeDef;
FUNCTION_StatusTypeDef _Recorder_Execution(RecorderPackageTypeDef* writePackage, uint32_t globalTime, Operating_Mode* stateOfCharger);
FUNCTION_StatusTypeDef _Write_Data_To_Flash(uint32_t Address, RecorderPackageTypeDef writePackage);
FUNCTION_StatusTypeDef _Recorder_Check(RecorderPackageTypeDef* readPackage, Operating_Mode* printSavedState);
FUNCTION_StatusTypeDef _Record_Data_Update(RecorderPackageTypeDef* writePackage, Operating_Mode* stateOfCharger, uint32_t chargeTime10ms);
FUNCTION_StatusTypeDef _Write_Package_Refresh(RecorderPackageTypeDef* writePackage);
FUNCTION_StatusTypeDef _Erase_Sector (uint32_t Address);
bool _Is_Memory_Blank(uint32_t Address);
void _Move_Data_From_Sector_to_Sector (uint32_t writeAddressOfOriginSector, uint32_t writeAddressOfDestinationSector);
void _Rearrage_Memory(void);
#endif /* SYSTEM_RECORDER_H_ */
