# Makefile for compiling a simple C++ program

# The compiler to use
CXX = g++

# Flags for the compiler
CXXFLAGS = -Wall -std=c++11

# The name of the executable
TARGET = end

# The source files
SRC = main.cpp load_balancer.cpp request.cpp web_server.cpp

# The object files (correspond to source files)
OBJ = $(SRC:.cpp=.o)

# The first target: how to create the executable
$(TARGET): $(OBJ)
	$(CXX)	$(CXXFLAGS)	-o	$(TARGET)	$(OBJ)

# Rule to create object files
%.o: %.cpp
	$(CXX)	$(CXXFLAGS) -c $<

# Clean up generated files
clean:
	rm -f	$(OBJ)	$(TARGET)