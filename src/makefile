
-include ../project.mk
-include ./libAdaptiveFilter/makefile
-include ./libdas/makefile


MAIN_APP_CPP= \
$(PROJECT_DIR)/src/mainMpi.cpp

# Tool invocations
mainApp: libdas.so
	@echo 'Building target: $@'
	mkdir -p $(BUILD_DIR)
	@echo 'Invoking: GCC C++ Linker'
	$(CXX) $(CXX_FLAGS) $(MAIN_APP_CPP) -o $(BUILD_DIR)/$@ -ldas
	@echo 'Finished building target: $@'
	@echo ' '

#########################################
