################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/littleFS/src/lfs.c \
../Middleware/littleFS/src/lfs_util.c 

C_DEPS += \
./Middleware/littleFS/src/lfs.d \
./Middleware/littleFS/src/lfs_util.d 

OBJS += \
./Middleware/littleFS/src/lfs.o \
./Middleware/littleFS/src/lfs_util.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/littleFS/src/%.o Middleware/littleFS/src/%.su: ../Middleware/littleFS/src/%.c Middleware/littleFS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/littleFS_W25Qxx/Middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/littleFS_W25Qxx/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-littleFS-2f-src

clean-Middleware-2f-littleFS-2f-src:
	-$(RM) ./Middleware/littleFS/src/lfs.d ./Middleware/littleFS/src/lfs.o ./Middleware/littleFS/src/lfs.su ./Middleware/littleFS/src/lfs_util.d ./Middleware/littleFS/src/lfs_util.o ./Middleware/littleFS/src/lfs_util.su

.PHONY: clean-Middleware-2f-littleFS-2f-src

