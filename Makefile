HEADERS =
SOURCES = matrix.cpp
OBJECTS = $(SOURCES:.cpp=.o)
MAIN_TARGET = matrix_executable

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

.PHONY: all clean run-main

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run-main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

clean:
	rm -f $(OBJECTS) $(MAIN_TARGET)