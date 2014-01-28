# folder locations
SRC_PATH := src
BUILD_PATH := build
OBJ_PATH := $(BUILD_PATH)/obj
DEP_PATH := $(BUILD_PATH)/deps

# compilers
CC := gcc
CXX := g++

# libraries
OPENGL_LIB := -lGL -lGLU -lglut

# cflags
CFLAGS := -Wall
CXXFLAGS := $(CFLAGS)
LDFLAGS := -lstdc++ $(OPENGL_LIB)

# files to compile
#C_SOURCES	:= $(wildcard $(SRC_PATH)/*.c)
CXX_SOURCES	:= $(wildcard $(SRC_PATH)/*.cpp)
DEP_FILES	:= $(patsubst $(SRC_PATH)/%.cpp, $(DEP_PATH)/%.d, $(CXX_SOURCES))
OBJ_FILES	:= $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(CXX_SOURCES))
BINARY		:= $(BUILD_PATH)/mm-sim

# global rule, depends on main binary
all: dirs $(BINARY)
	
dirs:
	mkdir -p $(DEP_PATH) $(BUILD_PATH) $(OBJ_PATH)

	
# rule to build main binary
$(BINARY): $(OBJ_FILES)
	@echo "Linking $(BINARY)"
	$(CXX) $(LDFLAGS) -o $(BINARY) $(OBJ_FILES)

# rule to build dependencies
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp
	echo -n "$(OBJ_PATH)/" > $@
	$(CXX) -MM $^ >> $@

# include the dependencies
-include $(DEP_FILES)

# general rule for object files
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
# delete the directories and put back in the structure
.PHONY:
clean:
	rm -rf $(BUILD_PATH)
	rm -rf $(DEP_PATH)
	
test:
	@echo "cpp sources: $(CXX_SOURCES)"
	@echo "dep files: $(DEP_FILES)"
	@echo "obj files: $(OBJ_FILES)"
