################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/src/I2C.c \
../Core/src/ILI9341.c \
../Core/src/IRQ.c \
../Core/src/LCD_1602.c \
../Core/src/RCC.c \
../Core/src/SPI_Functions.c \
../Core/src/basic_functions.c \
../Core/src/main.c 

OBJS += \
./Core/src/I2C.o \
./Core/src/ILI9341.o \
./Core/src/IRQ.o \
./Core/src/LCD_1602.o \
./Core/src/RCC.o \
./Core/src/SPI_Functions.o \
./Core/src/basic_functions.o \
./Core/src/main.o 

C_DEPS += \
./Core/src/I2C.d \
./Core/src/ILI9341.d \
./Core/src/IRQ.d \
./Core/src/LCD_1602.d \
./Core/src/RCC.d \
./Core/src/SPI_Functions.d \
./Core/src/basic_functions.d \
./Core/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/src/%.o Core/src/%.su Core/src/%.cyclo: ../Core/src/%.c Core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/CMSIS/Inc" -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/Core/Inc" -I"C:/Users/AnastasII/Desktop/GIT/STM32_project/FreeRTOS/inc" -I"C:/Users/AnastasII/Desktop/GIT/STM32_project/FreeRTOS/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-src

clean-Core-2f-src:
	-$(RM) ./Core/src/I2C.cyclo ./Core/src/I2C.d ./Core/src/I2C.o ./Core/src/I2C.su ./Core/src/ILI9341.cyclo ./Core/src/ILI9341.d ./Core/src/ILI9341.o ./Core/src/ILI9341.su ./Core/src/IRQ.cyclo ./Core/src/IRQ.d ./Core/src/IRQ.o ./Core/src/IRQ.su ./Core/src/LCD_1602.cyclo ./Core/src/LCD_1602.d ./Core/src/LCD_1602.o ./Core/src/LCD_1602.su ./Core/src/RCC.cyclo ./Core/src/RCC.d ./Core/src/RCC.o ./Core/src/RCC.su ./Core/src/SPI_Functions.cyclo ./Core/src/SPI_Functions.d ./Core/src/SPI_Functions.o ./Core/src/SPI_Functions.su ./Core/src/basic_functions.cyclo ./Core/src/basic_functions.d ./Core/src/basic_functions.o ./Core/src/basic_functions.su ./Core/src/main.cyclo ./Core/src/main.d ./Core/src/main.o ./Core/src/main.su

.PHONY: clean-Core-2f-src

