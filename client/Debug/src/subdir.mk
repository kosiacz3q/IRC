################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientProtocolExecutor.cpp \
../src/RequestResponseManager.cpp \
../src/client.cpp 

OBJS += \
./src/ClientProtocolExecutor.o \
./src/RequestResponseManager.o \
./src/client.o 

CPP_DEPS += \
./src/ClientProtocolExecutor.d \
./src/RequestResponseManager.d \
./src/client.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../core -I../../core/client -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


