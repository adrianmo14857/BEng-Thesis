################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/pololu/subdir.mk
-include libraries/gtest/subdir.mk
-include libraries/Wire/src/subdir.mk
-include libraries/Time/subdir.mk
-include libraries/SPI/src/subdir.mk
-include libraries/Rosserial_Arduino_Library/src/subdir.mk
-include libraries/PID/subdir.mk
-include libraries/IMU/src/subdir.mk
-include core/variant/subdir.mk
-include core/core/stm32/HAL/subdir.mk
-include core/core/stm32/subdir.mk
-include core/core/avr/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/adrian/ws/myTurtlebot_core/Release/arduino.ar \

ELF += \
myTurtlebot_core.elf \

HEX += \
myTurtlebot_core.hex \


# All Target
all:
	$(MAKE) --no-print-directory pre-build
	$(MAKE) --no-print-directory main-build

# Main-build Target
main-build: myTurtlebot_core

# Tool invocations
myTurtlebot_core: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/adrian/sloeber//arduinoPlugin/packages/STM32/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi-size" -A "/home/adrian/ws/myTurtlebot_core/Release/myTurtlebot_core.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/adrian/ws/myTurtlebot_core/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/adrian/sloeber//arduinoPlugin/packages/STM32/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi-gcc-ar" rcs     /home/adrian/ws/myTurtlebot_core/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

myTurtlebot_core.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/adrian/sloeber//arduinoPlugin/packages/STM32/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi-gcc" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -g -Og  -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align "-T/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/variants/NUCLEO_L476RG/ldscript.ld" "-Wl,-Map,/home/adrian/ws/myTurtlebot_core/Release/myTurtlebot_core.map"   "-L/home/adrian/sloeber//arduinoPlugin/packages/STM32/tools/CMSIS/5.3.0/CMSIS/Lib/GCC/" -larm_cortexM4l_math -o "/home/adrian/ws/myTurtlebot_core/Release/myTurtlebot_core.elf" "-L/home/adrian/ws/myTurtlebot_core/Release" -Wl,--start-group   $(LINK_OBJ)  -Wl,--whole-archive  /home/adrian/ws/myTurtlebot_core/Release/arduino.ar  -Wl,--no-whole-archive -lc -Wl,--end-group -lm -lgcc -lstdc++ --specs=nano.specs
	@echo 'Finished building: $@'
	@echo ' '

myTurtlebot_core.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${A.RECIPE.OBJCOPY.BIN.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

pre-build:
	-${A.RECIPE.HOOKS.PREBUILD.1.PATTERN}
	-@echo ' '

.PHONY: all clean dependents main-build pre-build

-include ../makefile.targets
