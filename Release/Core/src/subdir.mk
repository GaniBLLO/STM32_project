################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/src/RCC.c \
../Core/src/main.c \
../Core/src/timing_file.c 

OBJS += \
./Core/src/RCC.o \
./Core/src/main.o \
./Core/src/timing_file.o 

C_DEPS += \
./Core/src/RCC.d \
./Core/src/main.d \
./Core/src/timing_file.d 


# Each subdirectory must supply rules for building sources it contributes
Core/src/%.o Core/src/%.su Core/src/%.cyclo: ../Core/src/%.c Core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/CMSIS/Inc" -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/Core/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-src

clean-Core-2f-src:
	-$(RM) ./Core/src/RCC.cyclo ./Core/src/RCC.d ./Core/src/RCC.o ./Core/src/RCC.su ./Core/src/main.cyclo ./Core/src/main.d ./Core/src/main.o ./Core/src/main.su ./Core/src/timing_file.cyclo ./Core/src/timing_file.d ./Core/src/timing_file.o ./Core/src/timing_file.su

.PHONY: clean-Core-2f-src

