
RM := rm -rf

-include project.mk
-include ./src/makefile
-include ./src/libAdaptiveFilter/makefile
-include ./src/libdas/makefile

# All Target
all: mainApp

# Other Targets
das.clean:
	-$(RM) $(BUILD_DIR)
	-@echo ' '

clean: das.clean libaf.clean


