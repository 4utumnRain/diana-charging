################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-67703119: ../MSPM0G3505.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.18.0/sysconfig_cli.bat" -s "C:/ti/mspm0_sdk_2_02_00_05/.metadata/product.json" --script "D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/MSPM0G3505.syscfg" -o "syscfg" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/device_linker.cmd: build-67703119 ../MSPM0G3505.syscfg
syscfg/device.opt: build-67703119
syscfg/device.cmd.genlibs: build-67703119
syscfg/ti_msp_dl_config.c: build-67703119
syscfg/ti_msp_dl_config.h: build-67703119
syscfg/Event.dot: build-67703119
syscfg/: build-67703119

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_02_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


