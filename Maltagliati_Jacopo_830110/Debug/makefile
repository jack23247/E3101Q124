################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Maltagliati_Jacopo_830110.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Maltagliati_Jacopo_830110.list \

OBJCOPY_BIN += \
Maltagliati_Jacopo_830110.bin \


# All Target
all: Maltagliati_Jacopo_830110.elf secondary-outputs

# Tool invocations
Maltagliati_Jacopo_830110.elf: $(OBJS) $(USER_OBJS) C:\Users\quartz\Desktop\Maltagliati_Jacopo_830110\STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "Maltagliati_Jacopo_830110.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\quartz\Desktop\Maltagliati_Jacopo_830110\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Maltagliati_Jacopo_830110.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Maltagliati_Jacopo_830110.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Maltagliati_Jacopo_830110.list"
	@echo 'Finished building: $@'
	@echo ' '

Maltagliati_Jacopo_830110.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Maltagliati_Jacopo_830110.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
