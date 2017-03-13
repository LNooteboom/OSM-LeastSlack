################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Job.cpp \
../JobShop.cpp \
../Machine.cpp \
../Main.cpp \
../Task.cpp 

OBJS += \
./Job.o \
./JobShop.o \
./Machine.o \
./Main.o \
./Task.o 

CPP_DEPS += \
./Job.d \
./JobShop.d \
./Machine.d \
./Main.d \
./Task.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


