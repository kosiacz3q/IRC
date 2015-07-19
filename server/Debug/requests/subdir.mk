################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../requests/ConnectionRequestHandler.cpp 

OBJS += \
./requests/ConnectionRequestHandler.o 

CPP_DEPS += \
./requests/ConnectionRequestHandler.d 


# Each subdirectory must supply rules for building sources it contributes
requests/%.o: ../requests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I"/home/lucas/workspace/sopy/SOP/kosiak/core" -I"/home/lucas/workspace/sopy/SOP/kosiak/core/contract" -I"/home/lucas/workspace/sopy/SOP/kosiak/core/queueHandler" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


