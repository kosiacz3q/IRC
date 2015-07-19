################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/commands/AddToFriendsCommandHandler.cpp \
../src/commands/ConnectCommandHandler.cpp \
../src/commands/DisconnectCommandHandler.cpp \
../src/commands/JoinChannelCommand.cpp \
../src/commands/LeaveChannelCommandHandler.cpp \
../src/commands/ListChannelsCommand.cpp \
../src/commands/ListUsersCommandHandler.cpp \
../src/commands/SendMessageCommand.cpp \
../src/commands/SendPrivateMessage.cpp \
../src/commands/UnknownCommandHandler.cpp 

OBJS += \
./src/commands/AddToFriendsCommandHandler.o \
./src/commands/ConnectCommandHandler.o \
./src/commands/DisconnectCommandHandler.o \
./src/commands/JoinChannelCommand.o \
./src/commands/LeaveChannelCommandHandler.o \
./src/commands/ListChannelsCommand.o \
./src/commands/ListUsersCommandHandler.o \
./src/commands/SendMessageCommand.o \
./src/commands/SendPrivateMessage.o \
./src/commands/UnknownCommandHandler.o 

CPP_DEPS += \
./src/commands/AddToFriendsCommandHandler.d \
./src/commands/ConnectCommandHandler.d \
./src/commands/DisconnectCommandHandler.d \
./src/commands/JoinChannelCommand.d \
./src/commands/LeaveChannelCommandHandler.d \
./src/commands/ListChannelsCommand.d \
./src/commands/ListUsersCommandHandler.d \
./src/commands/SendMessageCommand.d \
./src/commands/SendPrivateMessage.d \
./src/commands/UnknownCommandHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/commands/%.o: ../src/commands/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../core -I../../core/client -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


