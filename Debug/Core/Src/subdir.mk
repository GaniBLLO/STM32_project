################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/I2C.c \
../Core/Src/ILI9341.c \
../Core/Src/IRQ.c \
../Core/Src/LCD_1602.c \
../Core/Src/RCC.c \
../Core/Src/SPI_Functions.c \
../Core/Src/basic_functions.c \
../Core/Src/main.c \
../Core/Src/timing_file.c 

OBJS += \
./Core/Src/I2C.o \
./Core/Src/ILI9341.o \
./Core/Src/IRQ.o \
./Core/Src/LCD_1602.o \
./Core/Src/RCC.o \
./Core/Src/SPI_Functions.o \
./Core/Src/basic_functions.o \
./Core/Src/main.o \
./Core/Src/timing_file.o 

C_DEPS += \
./Core/Src/I2C.d \
./Core/Src/ILI9341.d \
./Core/Src/IRQ.d \
./Core/Src/LCD_1602.d \
./Core/Src/RCC.d \
./Core/Src/SPI_Functions.d \
./Core/Src/basic_functions.d \
./Core/Src/main.d \
./Core/Src/timing_file.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/GaniBLLO/Desktop/GIT_CMSIS/STM32_project/CMSIS/Inc" -I"C:/Users/GaniBLLO/Desktop/GIT_CMSIS/STM32_project/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/I2C.d ./Core/Src/I2C.o ./Core/Src/I2C.su ./Core/Src/ILI9341.d ./Core/Src/ILI9341.o ./Core/Src/ILI9341.su ./Core/Src/IRQ.d ./Core/Src/IRQ.o ./Core/Src/IRQ.su ./Core/Src/LCD_1602.d ./Core/Src/LCD_1602.o ./Core/Src/LCD_1602.su ./Core/Src/RCC.d ./Core/Src/RCC.o ./Core/Src/RCC.su ./Core/Src/SPI_Functions.d ./Core/Src/SPI_Functions.o ./Core/Src/SPI_Functions.su ./Core/Src/basic_functions.d ./Core/Src/basic_functions.o ./Core/Src/basic_functions.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/timing_file.d ./Core/Src/timing_file.o ./Core/Src/timing_file.su

.PHONY: clean-Core-2f-Src

