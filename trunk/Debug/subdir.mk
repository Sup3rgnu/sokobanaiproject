################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../board.cpp \
../client.cpp \
../local_client.cpp \
../stdin_client.cpp 

OBJS += \
./board.o \
./client.o \
./local_client.o \
./stdin_client.o 

CPP_DEPS += \
./board.d \
./client.d \
./local_client.d \
./stdin_client.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


