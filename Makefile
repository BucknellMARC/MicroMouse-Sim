# folder locations
SRC_PATH := src
OBJ_PATH := build/obj
BUILD_PATH := build

# compilers
CC := gcc
CXX := gcc

# cflags
#CFLAGS := -Wall
CXXFLAGS := $(CFLAGS)

# files to compile
#C_SOURCES	:= $(wildcard $(SRC_PATH)/*.c)
CXX_SOURCES	:= $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES	:= $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(CXX_SOURCES))
BINARY		:= $(BUILD_PATH)/mm-sim

test:
	@echo cpp sources: $(CXX_SOURCES)
	@echo obj files: $(OBJ_FILES)

# global rule
all: $(BINARY)
	@echo "Hello World"