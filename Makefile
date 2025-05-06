# Compiler and flags
CXX = g++-14
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source and object files
SRC = main.cpp Game.cpp Room.cpp Player.cpp Item.cpp Entity.cpp
OBJ = $(SRC:.cpp=.o)

# Output binary
TARGET = game

# Default rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
