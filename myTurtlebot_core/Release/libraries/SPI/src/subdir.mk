################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/adrian/sloeber/arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/libraries/SPI/src/SPI.cpp 

LINK_OBJ += \
./libraries/SPI/src/SPI.cpp.o 

CPP_DEPS += \
./libraries/SPI/src/SPI.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/SPI/src/SPI.cpp.o: /home/adrian/sloeber/arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/libraries/SPI/src/SPI.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/adrian/sloeber//arduinoPlugin/packages/STM32/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi-g++" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb "@/home/adrian/ws/myTurtlebot_core/Release/sketch/build_opt.h" -c -g -Og -Wall -Wextra -std=gnu++14 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD "-I" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/cores/arduino/avr" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/cores/arduino/stm32" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/Drivers/STM32L4xx_HAL_Driver/Inc/" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/Drivers/STM32L4xx_HAL_Driver/Src/" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/STM32L4xx/" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/variants/NUCLEO_L476RG/usb" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/Middlewares/ST/STM32_USB_Device_Library/Core/Src" -DSTM32L4xx -DARDUINO=10802 -DARDUINO_NUCLEO_L476RG -DARDUINO_ARCH_STM32 -DBOARD_NAME="NUCLEO_L476RG"  -DSTM32L476xx  -DHAL_UART_MODULE_ENABLED "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/tools/CMSIS/5.3.0/CMSIS/Core/Include/" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/Drivers/CMSIS/Device/ST/STM32L4xx/Include/" "-I/home/adrian/sloeber//arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/system/Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/gcc/"   -I"/home/adrian/sloeber/arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/cores/arduino" -I"/home/adrian/sloeber/arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/variants/NUCLEO_L476RG" -I"/home/adrian/sloeber/arduinoPlugin/libraries/IMU/MPU9250-master/src" -I"/home/adrian/sloeber/arduinoPlugin/libraries/msgs/common_msgs-jade-devel" -I"/home/adrian/sloeber/arduinoPlugin/libraries/PID/Arduino-PID" -I"/home/adrian/sloeber/arduinoPlugin/libraries/pololu/dual-vnh5019-motor-shield" -I"/home/adrian/sloeber/arduinoPlugin/libraries/ros_serial/rosserial-melodic" -I"/home/adrian/sloeber/arduinoPlugin/libraries/rosComm/ros_comm" -I"/home/adrian/sloeber/arduinoPlugin/libraries/Rosserial_Arduino_Library/0.7.9/src" -I"/home/adrian/sloeber/arduinoPlugin/libraries/Time/1.5.0" -I"/home/adrian/sloeber/arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/libraries/Wire/src" -I"/home/adrian/sloeber/arduinoPlugin/libraries/gtest/1.0.1" -I"/home/adrian/sloeber/arduinoPlugin/packages/STM32/hardware/stm32/1.3.0/libraries/SPI/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


