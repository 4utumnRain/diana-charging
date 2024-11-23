################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"lib/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


