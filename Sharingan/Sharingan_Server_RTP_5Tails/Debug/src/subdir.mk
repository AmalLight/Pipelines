################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Sharingan_Server_RTP_5Tails.cpp \
../src/demon.cpp 

OBJS += \
./src/Sharingan_Server_RTP_5Tails.o \
./src/demon.o 

CPP_DEPS += \
./src/Sharingan_Server_RTP_5Tails.d \
./src/demon.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


