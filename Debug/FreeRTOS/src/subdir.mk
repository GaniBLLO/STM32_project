################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/src/croutine.c \
../FreeRTOS/src/event_groups.c \
../FreeRTOS/src/heap_1.c \
../FreeRTOS/src/list.c \
../FreeRTOS/src/port.c \
../FreeRTOS/src/queue.c \
../FreeRTOS/src/stream_buffer.c \
../FreeRTOS/src/tasks.c \
../FreeRTOS/src/timers.c 

OBJS += \
./FreeRTOS/src/croutine.o \
./FreeRTOS/src/event_groups.o \
./FreeRTOS/src/heap_1.o \
./FreeRTOS/src/list.o \
./FreeRTOS/src/port.o \
./FreeRTOS/src/queue.o \
./FreeRTOS/src/stream_buffer.o \
./FreeRTOS/src/tasks.o \
./FreeRTOS/src/timers.o 

C_DEPS += \
./FreeRTOS/src/croutine.d \
./FreeRTOS/src/event_groups.d \
./FreeRTOS/src/heap_1.d \
./FreeRTOS/src/list.d \
./FreeRTOS/src/port.d \
./FreeRTOS/src/queue.d \
./FreeRTOS/src/stream_buffer.d \
./FreeRTOS/src/tasks.d \
./FreeRTOS/src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/src/%.o FreeRTOS/src/%.su FreeRTOS/src/%.cyclo: ../FreeRTOS/src/%.c FreeRTOS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/CMSIS/Inc" -I"C:/Users/AnastasII/Desktop/STM/CMSIS_C8t6/Core/Inc" -I"C:/Users/AnastasII/Desktop/GIT/STM32_project/FreeRTOS/inc" -I"C:/Users/AnastasII/Desktop/GIT/STM32_project/FreeRTOS/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-src

clean-FreeRTOS-2f-src:
	-$(RM) ./FreeRTOS/src/croutine.cyclo ./FreeRTOS/src/croutine.d ./FreeRTOS/src/croutine.o ./FreeRTOS/src/croutine.su ./FreeRTOS/src/event_groups.cyclo ./FreeRTOS/src/event_groups.d ./FreeRTOS/src/event_groups.o ./FreeRTOS/src/event_groups.su ./FreeRTOS/src/heap_1.cyclo ./FreeRTOS/src/heap_1.d ./FreeRTOS/src/heap_1.o ./FreeRTOS/src/heap_1.su ./FreeRTOS/src/list.cyclo ./FreeRTOS/src/list.d ./FreeRTOS/src/list.o ./FreeRTOS/src/list.su ./FreeRTOS/src/port.cyclo ./FreeRTOS/src/port.d ./FreeRTOS/src/port.o ./FreeRTOS/src/port.su ./FreeRTOS/src/queue.cyclo ./FreeRTOS/src/queue.d ./FreeRTOS/src/queue.o ./FreeRTOS/src/queue.su ./FreeRTOS/src/stream_buffer.cyclo ./FreeRTOS/src/stream_buffer.d ./FreeRTOS/src/stream_buffer.o ./FreeRTOS/src/stream_buffer.su ./FreeRTOS/src/tasks.cyclo ./FreeRTOS/src/tasks.d ./FreeRTOS/src/tasks.o ./FreeRTOS/src/tasks.su ./FreeRTOS/src/timers.cyclo ./FreeRTOS/src/timers.d ./FreeRTOS/src/timers.o ./FreeRTOS/src/timers.su

.PHONY: clean-FreeRTOS-2f-src

