################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../queueHandler/QueueException.cpp \
../queueHandler/QueueHandler.cpp \
../queueHandler/QueueHolder.cpp \
../queueHandler/QueueOwner.cpp 

OBJS += \
./queueHandler/QueueException.o \
./queueHandler/QueueHandler.o \
./queueHandler/QueueHolder.o \
./queueHandler/QueueOwner.o 

CPP_DEPS += \
./queueHandler/QueueException.d \
./queueHandler/QueueHandler.d \
./queueHandler/QueueHolder.d \
./queueHandler/QueueOwner.d 


# Each subdirectory must supply rules for building sources it contributes
queueHandler/%.o: ../queueHandler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/include/c++/4.9.1 -I/usr/include/c++ -I/usr/include -I/usr/include/c++/4.9.1/backward -O3 -Wall -std=c++11 -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


