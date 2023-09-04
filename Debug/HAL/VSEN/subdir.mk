################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/VSEN/VSEN.c 

OBJS += \
./HAL/VSEN/VSEN.o 

C_DEPS += \
./HAL/VSEN/VSEN.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/VSEN/%.o: ../HAL/VSEN/%.c HAL/VSEN/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


