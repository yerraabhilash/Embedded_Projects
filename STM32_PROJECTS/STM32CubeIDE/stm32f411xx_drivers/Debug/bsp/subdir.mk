################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/ds1307.c \
../bsp/lcd.c 

OBJS += \
./bsp/ds1307.o \
./bsp/lcd.o 

C_DEPS += \
./bsp/ds1307.d \
./bsp/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/%.o bsp/%.su bsp/%.cyclo: ../bsp/%.c bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"C:/STM32CubeIDE/stm32f411xx_drivers/bsp" -I"C:/STM32CubeIDE/stm32f411xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -specs=rdimon.specs -lc -lrdimon -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-bsp

clean-bsp:
	-$(RM) ./bsp/ds1307.cyclo ./bsp/ds1307.d ./bsp/ds1307.o ./bsp/ds1307.su ./bsp/lcd.cyclo ./bsp/lcd.d ./bsp/lcd.o ./bsp/lcd.su

.PHONY: clean-bsp

