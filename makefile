# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = main.cpp GameManager.cpp GameObject.cpp Player.cpp InputManager.cpp

# Output binary
TARGET = GalacticOddyssey

# Rule to build the target executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(SFML_LIBS)

# Clean up build files
clean:
	rm -f $(TARGET)
