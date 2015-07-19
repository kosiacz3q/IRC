################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ChannelManager.cpp \
../src/ClientsManager.cpp \
../src/ServerLogicExecutor.cpp \
../src/server.cpp 

OBJS += \
./src/ChannelManager.o \
./src/ClientsManager.o \
./src/ServerLogicExecutor.o \
./src/server.o 

CPP_DEPS += \
./src/ChannelManager.d \
./src/ClientsManager.d \
./src/ServerLogicExecutor.d \
./src/server.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../core -I../../core/client -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


