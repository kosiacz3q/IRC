################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/notifications/NotificationsHandler.cpp 

OBJS += \
./src/notifications/NotificationsHandler.o 

CPP_DEPS += \
./src/notifications/NotificationsHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/notifications/%.o: ../src/notifications/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../core -I../../core/client -O3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


