################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/requests/AddFriendRequestHandler.cpp \
../src/requests/ClientIdProvider.cpp \
../src/requests/ConnectionRequestHandler.cpp \
../src/requests/DisconnectionRequestHandler.cpp \
../src/requests/FriendManager.cpp \
../src/requests/JoinChannelRequest.cpp \
../src/requests/LeaveChannelRequestHandler.cpp \
../src/requests/ListChannelsRequest.cpp \
../src/requests/ListUsersInChannelRequestHandel.cpp \
../src/requests/MessagesSender.cpp \
../src/requests/NotificationCounter.cpp \
../src/requests/SendMessageRequestHandler.cpp \
../src/requests/SendPrivateMessageRequestHandler.cpp \
../src/requests/UnknownRequestHandler.cpp 

OBJS += \
./src/requests/AddFriendRequestHandler.o \
./src/requests/ClientIdProvider.o \
./src/requests/ConnectionRequestHandler.o \
./src/requests/DisconnectionRequestHandler.o \
./src/requests/FriendManager.o \
./src/requests/JoinChannelRequest.o \
./src/requests/LeaveChannelRequestHandler.o \
./src/requests/ListChannelsRequest.o \
./src/requests/ListUsersInChannelRequestHandel.o \
./src/requests/MessagesSender.o \
./src/requests/NotificationCounter.o \
./src/requests/SendMessageRequestHandler.o \
./src/requests/SendPrivateMessageRequestHandler.o \
./src/requests/UnknownRequestHandler.o 

CPP_DEPS += \
./src/requests/AddFriendRequestHandler.d \
./src/requests/ClientIdProvider.d \
./src/requests/ConnectionRequestHandler.d \
./src/requests/DisconnectionRequestHandler.d \
./src/requests/FriendManager.d \
./src/requests/JoinChannelRequest.d \
./src/requests/LeaveChannelRequestHandler.d \
./src/requests/ListChannelsRequest.d \
./src/requests/ListUsersInChannelRequestHandel.d \
./src/requests/MessagesSender.d \
./src/requests/NotificationCounter.d \
./src/requests/SendMessageRequestHandler.d \
./src/requests/SendPrivateMessageRequestHandler.d \
./src/requests/UnknownRequestHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/requests/%.o: ../src/requests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../core -I../../core/client -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


