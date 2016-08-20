
-include ../../project.mk

LIBAF_DIR=$(PROJECT_DIR)/src/libAdaptiveFilter
LIBAF_SOURCE_DIR=$(LIBAF_DIR)/source
LIBAF_INCLUDE_DIR=$(LIBAF_DIR)/include

LIBAF_BUILD_DIR=$(BUILD_DIR)/lib
LIBAF_BUILD_OBJ_DIR=$(LIBAF_BUILD_DIR)/adaptivefilterObj
LIBAF_BUILD_INC_DIR=$(LIBAF_BUILD_DIR)/adaptivefilter


LIBAF_PUBLIC_H += \
$(LIBAF_BUILD_INC_DIR)/ISystemFunction.h \
$(LIBAF_BUILD_INC_DIR)/LinearFunction.h\
$(LIBAF_BUILD_INC_DIR)/LmsFilter.h \
$(LIBAF_BUILD_INC_DIR)/NumberGenerator.h


# Add inputs and outputs from these tool invocations to the build variables 
LIBAF_CPP_SRCS += \
$(LIBAF_SOURCE_DIR)/LinearFunction.cpp \
$(LIBAF_SOURCE_DIR)/LmsFilter.cpp \
$(LIBAF_SOURCE_DIR)/NumberGenerator.cpp 

OBJS += \
$(LIBAF_BUILD_OBJ_DIR)/LinearFunction.o \
$(LIBAF_BUILD_OBJ_DIR)/LmsFilter.o \
$(LIBAF_BUILD_OBJ_DIR)/NumberGenerator.o 


# Each subdirectory must supply rules for building sources it contributes
$(LIBAF_BUILD_OBJ_DIR)/%.o: $(LIBAF_SOURCE_DIR)/%.cpp
	@echo 'Building file: $<'
	mkdir -p $(LIBAF_BUILD_OBJ_DIR)
	@echo 'Invoking: Compiler'
	$(CXX) $(CXX_FLAGS) -I"$(LIBAF_INCLUDE_DIR)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


# Tool invocations
libaf.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Archiver'
	ar -r  "libaf.a" $(OBJS)
	mv libaf.a $(LIBAF_BUILD_DIR)/
	-$(RM) $(LIBAF_BUILD_OBJ_DIR)
	mkdir -p $(LIBAF_BUILD_INC_DIR)
	@echo 'Finished building target: $@'
	@echo ' '


#copy headers
$(LIBAF_BUILD_INC_DIR)/%.h: $(LIBAF_INCLUDE_DIR)/%.h
	cp  "$<" "$@"

libaf.header: $(LIBAF_PUBLIC_H)

#################################################

#
# All Target for adaptive filter lib
libaf: libaf.a libaf.header


	