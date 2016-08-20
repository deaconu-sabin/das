
-include ../project.mk
-include ./libAdaptiveFilter/makefile
-include ./libdas/makefile


MAIN_APP_CPP= \
$(PROJECT_DIR)/src/mainMpi.cpp

TARGET=mainApp

# Tool invocations
mainApp: libaf libdas
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $(MAIN_APP_CPP) -o $(BUILD_DIR)/$(TARGET) -ldas
	cp $(PROJECT_DIR)/net.cfg $(BUILD_DIR)/
	@echo 'Finished building target: $@'
	@echo ' '

#########################################
