################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/src/system_stm32f1xx.c 

OBJS += \
./CMSIS/src/system_stm32f1xx.o 

C_DEPS += \
./CMSIS/src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/src/%.o CMSIS/src/%.su CMSIS/src/%.cyclo: ../CMSIS/src/%.c CMSIS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/CMSIS/Inc" -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/Core/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CMSIS-2f-src

clean-CMSIS-2f-src:
	-$(RM) ./CMSIS/src/system_stm32f1xx.cyclo ./CMSIS/src/system_stm32f1xx.d ./CMSIS/src/system_stm32f1xx.o ./CMSIS/src/system_stm32f1xx.su

.PHONY: clean-CMSIS-2f-src
