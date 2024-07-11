################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS\ Source/croutine.c \
../FreeRTOS\ Source/event_groups.c \
../FreeRTOS\ Source/list.c \
../FreeRTOS\ Source/queue.c \
../FreeRTOS\ Source/tasks.c \
../FreeRTOS\ Source/timers.c 

OBJS += \
./FreeRTOS\ Source/croutine.o \
./FreeRTOS\ Source/event_groups.o \
./FreeRTOS\ Source/list.o \
./FreeRTOS\ Source/queue.o \
./FreeRTOS\ Source/tasks.o \
./FreeRTOS\ Source/timers.o 

C_DEPS += \
./FreeRTOS\ Source/croutine.d \
./FreeRTOS\ Source/event_groups.d \
./FreeRTOS\ Source/list.d \
./FreeRTOS\ Source/queue.d \
./FreeRTOS\ Source/tasks.d \
./FreeRTOS\ Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS\ Source/croutine.o: ../FreeRTOS\ Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/croutine.d" -MT"FreeRTOS\ Source/croutine.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/event_groups.o: ../FreeRTOS\ Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/event_groups.d" -MT"FreeRTOS\ Source/event_groups.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/list.o: ../FreeRTOS\ Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/list.d" -MT"FreeRTOS\ Source/list.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/queue.o: ../FreeRTOS\ Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/queue.d" -MT"FreeRTOS\ Source/queue.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/tasks.o: ../FreeRTOS\ Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/tasks.d" -MT"FreeRTOS\ Source/tasks.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/timers.o: ../FreeRTOS\ Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\include" -I"D:\Materials - CUFE\EECE 25 dash\second year\second term\Embedded systems\Project\RTOS communication\Demo\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/timers.d" -MT"FreeRTOS\ Source/timers.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


