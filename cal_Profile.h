/*
 * Profile.h
 *
 *  Created on: 12 Mar 2024
 *      Author: DELL
 */

#ifndef CAL_PROFILE_H_
#define CAL_PROFILE_H_

#include <cal_FixedPointMath.h>
#include "ti_msp_dl_config.h"
#include "GlobalDefinitions.h"

#define _IS_PRECHARGE()      ((vbat_q14<(VDDCHRG_q14-2)))
#define _IS_BULK_CHARGE()    ((Charging_Stage==PRECHARGE) && (vbat_q14>VDDCHRG_q14))
#define _IS_FULL()           ((vbat_q14>=VBULK_q14) && (ibat_q14<=IPRE_q14))

#define _IS_PRECHARGE_MOD_Q()      ((vbat_q14<(VDDCHRG_q14-2)))
#define _IS_BULK_CHARGE_MOD_Q()    ((Charging_Stage==PRECHARGE) && (vbat_q14>VDDCHRG_q14))
#define _IS_FULL_MOD_Q()           ((vbat_q9>=VBULK_q9) && (ibat_q9<=IPRE_q9))

#define TIMEOUT_PRECHARGE    900000U
#define TIMEOUT_BULKCHARGE1  2880000U
#define TIMEOUT_BULKCHARGE2  2880000U

#define _IS_DERATING()              ((temp_ADC>LOWTEMP_ADC)&&(temp_ADC<HIGHTEMP_ADC))
#define _IS_NORMAL_TEMPERATURE()    (temp_ADC<=LOWTEMP_ADC)

uint16_t    _PRFL_lookup3StageCharging(uint32_t vbat_q14, uint32_t ibat_q14, ChargingProfileParams *CHARGINGPARAMS);
uint16_t    _PRFL_lookup3StageCharging_modified_Q(uint32_t vbat_q14, uint32_t ibat_q9, ChargingProfileParams *CHARGINGPARAMS);
uint32_t    PRFL_getTemperatureDeratingCurrent(uint16_t temp_ADC);
uint32_t    PRFL_getTemperatureDeratingFAN(uint16_t temp_ADC);

#endif /* CAL_PROFILE_H_ */
