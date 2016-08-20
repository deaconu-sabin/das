
-include ../../project.mk

LIBDAS_CPP= \
AlgorithmLoader.cpp \
Config.cpp \
Logging.cpp \
Network.cpp

TARGET=libdas.so



# Tool invocations
libdas:
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	mkdir -p $(LIB_DIR)
	$(MPICXX) $(CXX_FLAGS) $(SHARED_LIB) $(LIBDAS_CPP) -o $(LIB_DIR)/$(TARGET)
	@echo 'Finished building target: $@'
	@echo ' '

#########################################

all: libdas

# Other Targets
clean:
	-$(RM) $(LIB_DIR)/$(TARGET)
	-@echo ' '

.PHONY: all clean 
.SECONDARY: