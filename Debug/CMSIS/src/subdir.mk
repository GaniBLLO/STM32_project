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
CMSIS/src/%.o CMSIS/src/%.su: ../CMSIS/src/%.c CMSIS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/GaniBLLO/Desktop/GIT_CMSIS/STM32_project/CMSIS/Inc" -I"C:/Users/GaniBLLO/Desktop/GIT_CMSIS/STM32_project/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CMSIS-2f-src

clean-CMSIS-2f-src:
	-$(RM) ./CMSIS/src/system_stm32f1xx.d ./CMSIS/src/system_stm32f1xx.o ./CMSIS/src/system_stm32f1xx.su

.PHONY: clean-CMSIS-2f-src

