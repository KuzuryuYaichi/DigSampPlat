################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/OLED/display_ctrl.c \
../src/OLED/oled.c 

OBJS += \
./src/OLED/display_ctrl.o \
./src/OLED/oled.o 

C_DEPS += \
./src/OLED/display_ctrl.d \
./src/OLED/oled.d 


# Each subdirectory must supply rules for building sources it contributes
src/OLED/%.o: ../src/OLED/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../16ch_cpu0_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


