################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
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

BUILD_ARTIFACT_NAME := OOEDO_SAMURAI
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
OOEDO_SAMURAI.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
OOEDO_SAMURAI.list \

OBJCOPY_HEX += \
OOEDO_SAMURAI.hex \

OBJCOPY_BIN += \
OOEDO_SAMURAI.bin \


# All Target
all: main-build

# Main-build Target
main-build: OOEDO_SAMURAI.elf secondary-outputs

# Tool invocations
OOEDO_SAMURAI.elf: $(OBJS) $(USER_OBJS) C:\Users\sssho\STM32CubeIDE\workspace_robomaster\OOEDO_SAMURAI\STM32F405RGTX_FLASH.ld
	arm-none-eabi-gcc -o "OOEDO_SAMURAI.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\sssho\STM32CubeIDE\workspace_robomaster\OOEDO_SAMURAI\STM32F405RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="OOEDO_SAMURAI.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

OOEDO_SAMURAI.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "OOEDO_SAMURAI.list"
	@echo 'Finished building: $@'
	@echo ' '

OOEDO_SAMURAI.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "OOEDO_SAMURAI.hex"
	@echo 'Finished building: $@'
	@echo ' '

OOEDO_SAMURAI.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "OOEDO_SAMURAI.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
