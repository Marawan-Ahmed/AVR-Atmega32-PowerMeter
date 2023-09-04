################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/ACS712/ACS712.c 

OBJS += \
./HAL/ACS712/ACS712.o 

C_DEPS += \
./HAL/ACS712/ACS712.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/ACS712/%.o: ../HAL/ACS712/%.c HAL/ACS712/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


