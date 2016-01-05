
RM := rm -rf

CPP_SRCS += \
../src/NetworkSim.cpp \
./mainMpi.cpp


# All Target
all: MpiApp

# Tool invocations
MpiApp:
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	mpic++  -o "MpiApp" $(CPP_SRCS) -I"../src/"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MpiApp
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

