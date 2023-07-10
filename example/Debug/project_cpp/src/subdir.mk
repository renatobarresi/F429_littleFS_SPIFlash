################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../project_cpp/src/project_cpp.cpp 

OBJS += \
./project_cpp/src/project_cpp.o 

CPP_DEPS += \
./project_cpp/src/project_cpp.d 


# Each subdirectory must supply rules for building sources it contributes
project_cpp/src/%.o project_cpp/src/%.su: ../project_cpp/src/%.cpp project_cpp/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/littleFS_W25Qxx/Middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/littleFS_W25Qxx/modules/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/littleFS_W25Qxx/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_cpp-2f-src

clean-project_cpp-2f-src:
	-$(RM) ./project_cpp/src/project_cpp.d ./project_cpp/src/project_cpp.o ./project_cpp/src/project_cpp.su

.PHONY: clean-project_cpp-2f-src

