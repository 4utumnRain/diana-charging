################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS

GEN_OPTS__FLAG := @"syscfg/device.opt" 
GEN_CMDS__FLAG := -Wl,-l"syscfg/device_linker.cmd" 

ORDERED_OBJS += \
"./GlobalDefinitions.o" \
"./syscfg/ti_msp_dl_config.o" \
"./startup_mspm0g350x_ticlang.o" \
"./System_Recorder.o" \
"./UARTLib.o" \
"./app_EbikeCharger.o" \
"./cal_Controller.o" \
"./cal_FixedPointMath.o" \
"./cal_Profile.o" \
"./drv_BotLayer.o" \
"./main.o" \
$(GEN_CMDS__FLAG) \
-Wl,-ldevice.cmd.genlibs \
-Wl,-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode.out \

EXE_OUTPUTS__QUOTED += \
"RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode.out" \


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode.out"

# Tool invocations
RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS/bin/tiarmclang.exe" @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -gdwarf-3 -Wl,-m"RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode.map" -Wl,-i"C:/ti/mspm0_sdk_2_02_00_05/source" -Wl,-i"D:/OneDrive - Hanoi University of Science and Technology/Lab/All_temp/18-11-2024-Code Tran Ngat/RC.2_1.0.0.2_PROE_60V3A_SourceCode/Debug/syscfg" -Wl,-i"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-armllvm_3.2.0.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode_linkInfo.xml" -Wl,--rom_model -o "RC.2_1.0.0.2_PROE_60V3A_DianaPOC_SourceCode.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "GlobalDefinitions.o" "syscfg\ti_msp_dl_config.o" "startup_mspm0g350x_ticlang.o" "System_Recorder.o" "UARTLib.o" "app_EbikeCharger.o" "cal_Controller.o" "cal_FixedPointMath.o" "cal_Profile.o" "drv_BotLayer.o" "main.o" 
	-$(RM) "GlobalDefinitions.d" "syscfg\ti_msp_dl_config.d" "startup_mspm0g350x_ticlang.d" "System_Recorder.d" "UARTLib.d" "app_EbikeCharger.d" "cal_Controller.d" "cal_FixedPointMath.d" "cal_Profile.d" "drv_BotLayer.d" "main.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

