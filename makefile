
RM := rm -rf

-include project.mk
-include ./src/makefile
-include ./src/libAdaptiveFilter/makefile
-include ./src/libdas/makefile

# All Target
all: mainApp
	cp -r $(PROJECT_SRC_DIR)/include     $(BUILD_DIR)/
	cp -r $(PROJECT_SRC_DIR)/algorithms  $(BUILD_DIR)/
	cp    $(PROJECT_DIR)/Network.cfg     $(BUILD_DIR)/
	

# Other Targets
clean:
	-$(RM) $(BUILD_DIR)/*
	-@echo ' '


