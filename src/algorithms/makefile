
RM := rm -rf

CXX=g++
CXX_FLAGS=-O0 \-g3 -I../include -L../lib -fPIC -shared

ALGORITHMS_CPP_FILES := $(wildcard *.cpp)
ALGORITHMS=$(ALGORITHMS_CPP_FILES:%Algorithm.cpp=%.algorithm)


%.algorithm: %Algorithm.cpp
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CXX) $(CXX_FLAGS) $(SHARED_LIB) -o $@  $<
	@echo 'Finished building target: $@'
	@echo ' '

# Tool invocations
all: $(ALGORITHMS)

clean:
	$(RM) *.algorithm

#########################################