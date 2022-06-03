################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RTP_5Tails_thread.cpp \
../src/Sharingan_Client_RTP_5Tails.cpp 

OBJS += \
./src/RTP_5Tails_thread.o \
./src/Sharingan_Client_RTP_5Tails.o 

CPP_DEPS += \
./src/RTP_5Tails_thread.d \
./src/Sharingan_Client_RTP_5Tails.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/lib/wx/include/gtk2-unicode-3.1 -I/usr/local/include/wx-3.1 -O3 -Wall -c -fmessage-length=0 `wx-config --cxxflags` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


