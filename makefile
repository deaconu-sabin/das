
RM := rm -rf

-include project.mk
-include src/libAdaptiveFilter/makefile

CPP_SRCS += \
./src/network/NetworkSim.cpp \
./src/network/Node.cpp \
./src/mainMpi.cpp

EXECUTABLE=$(BUILD_DIR)/das

# All Target
all: libaf  das

# Tool invocations
das: 
	@echo 'Building target: $@'
	@echo 'Invoking: MPI C++ Linker'
	$(MPICXX) -I"$(LIBAF_BUILD_DIR)" -o $(EXECUTABLE) $(CPP_SRCS) $(LIBAF_BUILD_DIR)/libaf.a 
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
das.clean:
	-$(RM) $(EXECUTABLE)
	-@echo ' '

clean: das.clean libaf.clean


