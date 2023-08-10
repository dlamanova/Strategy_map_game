# Makefile for tietoervy_daria_lamanova project

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS :=

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Targets
EXECUTABLE := $(BIN_DIR)/tietoervy_daria_lamanova

# Phony targets
.PHONY: all clean

# Build rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

# Clean rule
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Dependencies
$(OBJS): | $(OBJ_DIR)
$(EXECUTABLE): | $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)
