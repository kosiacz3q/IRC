################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessageFactory/MessageFactory.cpp 

OBJS += \
./MessageFactory/MessageFactory.o 

CPP_DEPS += \
./MessageFactory/MessageFactory.d 


# Each subdirectory must supply rules for building sources it contributes
MessageFactory/%.o: ../MessageFactory/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -std=c++11 -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


