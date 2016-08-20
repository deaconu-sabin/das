
-include ../project.mk

EXEDAS_CPP= \
mainMpi.cpp

TARGET=das

# Tool invocations
das:
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $(EXEDAS_CPP) -o $(BUILD_DIR)/$(TARGET) -ldas
	cp net.cfg $(BUILD_DIR)/
	@echo 'Finished building target: $@'
	@echo ' '

#########################################

all: das

# Other Targets
clean:
	-$(RM) $(BUILD_DIR)/$(TARGET)
	-@echo ' '

.PHONY: all clean 
.SECONDARY: