# folder locations
SRC_PATH := src
OBJ_PATH := build/obj
BUILD_PATH := build

# compilers
CC := gcc
CXX := gcc

# cflags
CFLAGS := -Wall
CXXFLAGS := $(CFLAGS)

# files to compile
#C_SOURCES	:= $(wildcard $(SRC_PATH)/*.c)
CXX_SOURCES	:= $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES	:= $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(CXX_SOURCES))
BINARY		:= $(BUILD_PATH)/mm-sim


# global rule
all: $(BINARY)
	
$(BINARY): $(OBJ_FILES)
	@echo "Linking $(BINARY)"
	$(CXX) -o $(BINARY) $(OBJ_FILES)
	
$(OBJ_PATH)/%.o: $(CXX_SOURCES) #$(SRC_PATH)/%.cpp
	@echo "Building: $@"
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
# delete the directories and put back in the structure
clean:
	rm -rf $(BUILD_PATH)
	mkdir $(BUILD_PATH)
	mkdir $(OBJ_PATH)
	
test:
	@echo cpp sources: $(CXX_SOURCES)
	@echo obj files: $(OBJ_FILES)