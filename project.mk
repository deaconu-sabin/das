
RM := rm -rf

PROJECT_DIR=.
PROJECT_SRC_DIR=$(PROJECT_DIR)/src
PROJECT_INC_DIR=$(PROJECT_DIR)/src/include

BUILD_DIR=$(PROJECT_DIR)/build
LIB_DIR=$(BUILD_DIR)/lib

CXX=g++
CXX_FLAGS=-O0 \-g3 -I$(PROJECT_INC_DIR) -L$(LIB_DIR)
SHARED_LIB=-fPIC -shared

MPICXX=mpic++ 