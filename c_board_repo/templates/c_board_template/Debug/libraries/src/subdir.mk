################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/BMI088.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_B2B.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_Core.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_Damiao.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_RMMotors.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/DBUS_DR16.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/PID.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/TIMER.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/UART_Core.c \
C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/test_lib.c 

OBJS += \
./libraries/src/BMI088.o \
./libraries/src/CAN_B2B.o \
./libraries/src/CAN_Core.o \
./libraries/src/CAN_Damiao.o \
./libraries/src/CAN_RMMotors.o \
./libraries/src/DBUS_DR16.o \
./libraries/src/PID.o \
./libraries/src/TIMER.o \
./libraries/src/UART_Core.o \
./libraries/src/test_lib.o 

C_DEPS += \
./libraries/src/BMI088.d \
./libraries/src/CAN_B2B.d \
./libraries/src/CAN_Core.d \
./libraries/src/CAN_Damiao.d \
./libraries/src/CAN_RMMotors.d \
./libraries/src/DBUS_DR16.d \
./libraries/src/PID.d \
./libraries/src/TIMER.d \
./libraries/src/UART_Core.d \
./libraries/src/test_lib.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/src/BMI088.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/BMI088.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/CAN_B2B.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_B2B.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/CAN_Core.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_Core.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/CAN_Damiao.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_Damiao.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/CAN_RMMotors.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/CAN_RMMotors.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/DBUS_DR16.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/DBUS_DR16.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/PID.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/PID.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/TIMER.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/TIMER.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/UART_Core.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/UART_Core.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
libraries/src/test_lib.o: C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/src/test_lib.c libraries/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Niko/Documents/Robomaster/ASN_controls_repo/c_board_repo/libraries/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-libraries-2f-src

clean-libraries-2f-src:
	-$(RM) ./libraries/src/BMI088.cyclo ./libraries/src/BMI088.d ./libraries/src/BMI088.o ./libraries/src/BMI088.su ./libraries/src/CAN_B2B.cyclo ./libraries/src/CAN_B2B.d ./libraries/src/CAN_B2B.o ./libraries/src/CAN_B2B.su ./libraries/src/CAN_Core.cyclo ./libraries/src/CAN_Core.d ./libraries/src/CAN_Core.o ./libraries/src/CAN_Core.su ./libraries/src/CAN_Damiao.cyclo ./libraries/src/CAN_Damiao.d ./libraries/src/CAN_Damiao.o ./libraries/src/CAN_Damiao.su ./libraries/src/CAN_RMMotors.cyclo ./libraries/src/CAN_RMMotors.d ./libraries/src/CAN_RMMotors.o ./libraries/src/CAN_RMMotors.su ./libraries/src/DBUS_DR16.cyclo ./libraries/src/DBUS_DR16.d ./libraries/src/DBUS_DR16.o ./libraries/src/DBUS_DR16.su ./libraries/src/PID.cyclo ./libraries/src/PID.d ./libraries/src/PID.o ./libraries/src/PID.su ./libraries/src/TIMER.cyclo ./libraries/src/TIMER.d ./libraries/src/TIMER.o ./libraries/src/TIMER.su ./libraries/src/UART_Core.cyclo ./libraries/src/UART_Core.d ./libraries/src/UART_Core.o ./libraries/src/UART_Core.su ./libraries/src/test_lib.cyclo ./libraries/src/test_lib.d ./libraries/src/test_lib.o ./libraries/src/test_lib.su

.PHONY: clean-libraries-2f-src

