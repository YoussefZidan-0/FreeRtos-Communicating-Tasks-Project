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

C_DEPS += \
./FreeRTOS\ Source/croutine.d \
./FreeRTOS\ Source/event_groups.d \
./FreeRTOS\ Source/list.d \
./FreeRTOS\ Source/queue.d \
./FreeRTOS\ Source/tasks.d \
./FreeRTOS\ Source/timers.d 

OBJS += \
./FreeRTOS\ Source/croutine.o \
./FreeRTOS\ Source/event_groups.o \
./FreeRTOS\ Source/list.o \
./FreeRTOS\ Source/queue.o \
./FreeRTOS\ Source/tasks.o \
./FreeRTOS\ Source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS\ Source/croutine.o: ../FreeRTOS\ Source/croutine.c FreeRTOS\ Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/croutine.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/event_groups.o: ../FreeRTOS\ Source/event_groups.c FreeRTOS\ Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/event_groups.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/list.o: ../FreeRTOS\ Source/list.c FreeRTOS\ Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/list.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/queue.o: ../FreeRTOS\ Source/queue.c FreeRTOS\ Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/queue.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/tasks.o: ../FreeRTOS\ Source/tasks.c FreeRTOS\ Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/tasks.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS\ Source/timers.o: ../FreeRTOS\ Source/timers.c FreeRTOS\ Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\include" -I"C:\Users\white\source\repos\FreeRtos-Communicating-Tasks-Project\FreeRTOS Source\portable\GCC\ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"FreeRTOS Source/timers.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


