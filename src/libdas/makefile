
-include ../../project.mk

LIBDAS_SRC_DIR=$(PROJECT_DIR)/src/libdas

LIBDAS_CPP= \
$(LIBDAS_SRC_DIR)/AlgorithmLoader.cpp \
$(LIBDAS_SRC_DIR)/Config.cpp \
$(LIBDAS_SRC_DIR)/Logging.cpp \
$(LIBDAS_SRC_DIR)/Network.cpp


# Tool invocations
libdas.so:
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	mkdir -p $(LIB_DIR)
	$(MPICXX) $(CXX_FLAGS) $(SHARED_LIB) $(LIBDAS_CPP) -o $(LIB_DIR)/$@
	@echo 'Finished building target: $@'
	@echo ' '

#########################################
