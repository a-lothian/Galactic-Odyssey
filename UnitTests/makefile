# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source and header files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable
EXECUTABLE = $(BIN_DIR)/galactic_odyssey

# Default target: Build the project
all: $(EXECUTABLE)

# Link object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(SFML_LIBS)

# Compile .cpp files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Clean generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild the project
rebuild: clean all

# Target to clean everything except executable
.PHONY: all clean rebuild
