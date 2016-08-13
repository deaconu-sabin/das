
RM := rm -rf

PROJECT_DIR=/home/sabin/Projects/das
BUILD_DIR=$(PROJECT_DIR)/build

CXX=g++
CXX_FLAGS=-O0 \-g3 -Wall -c -fmessage-length=0 

MPICXX=mpic++