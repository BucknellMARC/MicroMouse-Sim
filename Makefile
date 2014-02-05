# folder locations
SRC_PATH := src
LOGIC_PATH := $(SRC_PATH)/logic
GRAPHICS_PATH := $(SRC_PATH)/graphics

BUILD_PATH := build
DEP_PATH := $(BUILD_PATH)/deps

# compilers
CC := gcc
CXX := g++

# libraries
OPENGL_LIB := -lGL -lGLU -lglut

# cflags
CFLAGS := -Wall -I $(SRC_PATH) -I $(LOGIC_PATH) -I $(GRAPHICS_PATH)
CXXFLAGS := $(CFLAGS)
LDFLAGS := -lstdc++ $(OPENGL_LIB)

# logic
LOGIC_SOURCES	:= $(wildcard $(LOGIC_PATH)/*.cpp)
LOGIC_NAMES		:= $(basename $(LOGIC_SOURCES))
LOGIC_DEP		:= $(addprefix $(DEP_PATH)/, $(notdir $(LOGIC_NAMES)))
LOGIC_DEP		:= $(addsuffix .logic.d, $(LOGIC_DEP))
LOGIC_OBJ		:= $(addprefix $(BUILD_PATH)/, $(notdir $(LOGIC_NAMES)))
LOGIC_OBJ		:= $(addsuffix .logic.o, $(LOGIC_OBJ))

# graphics
GRAPHICS_SOURCES	:= $(wildcard $(GRAPHICS_PATH)/*.cpp)
GRAPHICS_NAMES		:= $(basename $(GRAPHICS_SOURCES))
GRAPHICS_DEP		:= $(addprefix $(DEP_PATH)/, $(notdir $(GRAPHICS_NAMES)))
GRAPHICS_DEP		:= $(addsuffix .graphics.d, $(GRAPHICS_DEP))
GRAPHICS_OBJ		:= $(addprefix $(BUILD_PATH)/, $(notdir $(GRAPHICS_NAMES)))
GRAPHICS_OBJ		:= $(addsuffix .graphics.o, $(GRAPHICS_OBJ))

# the final application
BINARY := mm-sim

# global rule, depends on main binary
all: dirs $(BINARY)
	
dirs:
	mkdir -p $(DEP_PATH) $(BUILD_PATH)
	
# rule to build main binary
mm-sim: $(LOGIC_OBJ) $(GRAPHICS_OBJ) $(SRC_PATH)/main.cpp
	@echo "Linking $(BINARY)"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BINARY) $^

# rule to build dependencies
$(DEP_PATH)/%.graphics.d: $(SRC_PATH)/%.cpp
	echo -n "$(OBJ_PATH)/" > $@
	$(CXX) -MM $^ >> $@
	
$(DEP_PATH)/%.logic.d: $(SRC_PATH)/%.c
	echo -n "$(OBJ_PATH)/" > $@
	$(CXX) -MM $^ >> $@

# include the dependencies
-include $(LOGIC_DEP)
-include $(GRAPHICS_DEP)

$(BUILD_PATH)/%.logic.o: $(LOGIC_PATH)/%.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

$(BUILD_PATH)/%.graphics.o: $(GRAPHICS_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
# delete the directories and put back in the structure
.PHONY:
clean:
	rm -rf $(BUILD_PATH)
	rm -rf $(DEP_PATH)
	rm -f $(BINARY)
	
test:
	@echo Logic:
	@echo	src: $(LOGIC_SOURCES)
	@echo	dep: $(LOGIC_DEP)
	@echo	obj: $(LOGIC_OBJ)
	@echo
	@echo Graphics:
	@echo	src: $(GRAPHICS_SOURCES)
	@echo	dep: $(GRAPHICS_DEP)
	@echo	obj: $(GRAPHICS_OBJ)
