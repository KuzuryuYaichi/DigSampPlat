################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/fpga_ctrl.c \
../src/main.c \
../src/platform_zynq.c \
../src/shared.c \
../src/sleep.c \
../src/xscugic_tapp_example.c \
../src/xscutimer_intr_example.c \
../src/xtime_l.c 

OBJS += \
./src/fpga_ctrl.o \
./src/main.o \
./src/platform_zynq.o \
./src/shared.o \
./src/sleep.o \
./src/xscugic_tapp_example.o \
./src/xscutimer_intr_example.o \
./src/xtime_l.o 

C_DEPS += \
./src/fpga_ctrl.d \
./src/main.d \
./src/platform_zynq.d \
./src/shared.d \
./src/sleep.d \
./src/xscugic_tapp_example.d \
./src/xscutimer_intr_example.d \
./src/xtime_l.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../16ch_cpu1_bsp/ps7_cortexa9_1/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


