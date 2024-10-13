################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../BUZZER.c \
../DC_MOTOR.c \
../FLAME_SENSOR.c \
../GPIO.c \
../LCD.c \
../LDR_DRIVER.c \
../LED.c \
../LM35_DRIVER.c \
../PROJECT3_SmartHome.c \
../TIMER0_PWM_DRIVER.c 

OBJS += \
./ADC.o \
./BUZZER.o \
./DC_MOTOR.o \
./FLAME_SENSOR.o \
./GPIO.o \
./LCD.o \
./LDR_DRIVER.o \
./LED.o \
./LM35_DRIVER.o \
./PROJECT3_SmartHome.o \
./TIMER0_PWM_DRIVER.o 

C_DEPS += \
./ADC.d \
./BUZZER.d \
./DC_MOTOR.d \
./FLAME_SENSOR.d \
./GPIO.d \
./LCD.d \
./LDR_DRIVER.d \
./LED.d \
./LM35_DRIVER.d \
./PROJECT3_SmartHome.d \
./TIMER0_PWM_DRIVER.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


