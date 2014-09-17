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
CFLAGS := -Wall -I $(SRC_PATH)
CXXFLAGS := $(CFLAGS) -D GPP
LDFLAGS := -lstdc++ $(OPENGL_LIB)

# logic
LOGIC_SOURCES	:= $(wildcard $(LOGIC_PATH)/*.c)
LOGIC_NAMES		:= $(basename $(LOGIC_SOURCES))
LOGIC_DEP		:= $(addprefix $(DEP_PATH)/, $(notdir $(LOGIC_NAMES)))
LOGIC_DEP		:= $(addsuffix .d, $(LOGIC_DEP))
LOGIC_OBJ		:= $(addprefix $(BUILD_PATH)/, $(notdir $(LOGIC_NAMES)))
LOGIC_OBJ		:= $(addsuffix .o, $(LOGIC_OBJ))

# graphics
GRAPHICS_SOURCES	:= $(wildcard $(GRAPHICS_PATH)/*.cpp)
GRAPHICS_NAMES		:= $(basename $(GRAPHICS_SOURCES))
GRAPHICS_DEP		:= $(addprefix $(DEP_PATH)/, $(notdir $(GRAPHICS_NAMES)))
GRAPHICS_DEP		:= $(addsuffix .d, $(GRAPHICS_DEP))
GRAPHICS_OBJ		:= $(addprefix $(BUILD_PATH)/, $(notdir $(GRAPHICS_NAMES)))
GRAPHICS_OBJ		:= $(addsuffix .o, $(GRAPHICS_OBJ))

# the final application
BINARY := mm-sim

# global rule, depends on main binary
all: dirs $(LOGIC_DEP) $(GRAPHICS_DEP) $(BINARY)
	
dirs:
	mkdir -p $(DEP_PATH) $(BUILD_PATH)
	
# rule to build main binary
mm-sim: $(LOGIC_OBJ) $(GRAPHICS_OBJ) $(SRC_PATH)/main.cpp
	@echo -n "Linking mm-sim..."
	$(CXX) $(CXXFLAGS) -o $(BINARY) $^ $(LDFLAGS)
	@echo "done!"

# rule to build dependencies
$(DEP_PATH)/%.d: $(LOGIC_PATH)/%.c
	@mkdir -p $(DEP_PATH) $(BUILD_PATH)
	@echo -n "$(BUILD_PATH)/" > $@
	$(CC) $(CFLAGS) -MM $< >> $@

$(DEP_PATH)/%.d: $(GRAPHICS_PATH)/%.cpp
	@mkdir -p $(DEP_PATH) $(BUILD_PATH)
	@echo -n "$(BUILD_PATH)/" > $@
	$(CXX) $(CXXFLAGS) -MM $< >> $@

# include the dependencies
-include $(LOGIC_DEP)
-include $(GRAPHICS_DEP)

$(BUILD_PATH)/%.o: $(LOGIC_PATH)/%.c
	$(CC) -std=c99 $(CFLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(GRAPHICS_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
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
