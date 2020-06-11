# Commands
CXX = g++
CXXFLAGS = -Wall -g
RM = rm -f
MKDIR = mkdir -p

# Source locations
SRC_DIR = ./src
PROJECT_DIR = .

# Include paths
INCLUDES = -Isrc -Iinc -I$(SRC_DIR)

# Output files
BIN_DIR = ./bin
OUTPUT_BIN = straights

OBJECT_FILES = $(addsuffix .o, $(basename $(notdir $(wildcard $(SRC_DIR)/*.cpp))))
OBJECTS = $(addprefix $(BIN_DIR)/, $(OBJECT_FILES))

.PHONY: all stage clean

# vpath
vpath
vpath %.cpp $(SRC_DIR)/

all: $(OUTPUT_BIN)

$(BIN_DIR)/%.o: %.cpp
	@echo "building $@ from $^..."
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(OUTPUT_BIN): stage $(OBJECTS)
	$(CXX) $(INCLUDES) $(CCXFLAGS) -o $(OUTPUT_BIN) $(filter %.o, $^)

stage:
ifeq (,$(wildcard $(BIN_DIR)))
	@echo "creating binary directory..."
	$(MKDIR) $(BIN_DIR)
endif

clean:
	@echo "cleaning project..."
ifneq (,$(wildcard $(BIN_DIR)))
	$(RM) $(BIN_DIR)/*
endif
	$(RM) $(PROJECT_DIR)/$(OUTPUT_BIN)
