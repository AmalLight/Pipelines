################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RTP_thread.cpp \
../src/Sharingan_Client_RTP.cpp 

OBJS += \
./src/RTP_thread.o \
./src/Sharingan_Client_RTP.o 

CPP_DEPS += \
./src/RTP_thread.d \
./src/Sharingan_Client_RTP.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


