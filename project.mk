
RM := rm -rf

PROJECT_DIR=/home/sabin/Projects/das
BUILD_DIR=$(PROJECT_DIR)/build
LIB_DIR=$(BUILD_DIR)/lib
INC_DIR=$(PROJECT_DIR)/src/include

CXX=g++
CXX_FLAGS=-O0 \-g3 -I$(INC_DIR) -L$(LIB_DIR)
SHARED_LIB=-fPIC -shared

MPICXX=mpic++ 