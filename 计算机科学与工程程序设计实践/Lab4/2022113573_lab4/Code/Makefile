## MAKEFILE

CXX = g++
CXXFLAGS = -c -g
TARGET = management

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
.PHONY: clean
clean:
	rm -f *.o $(TARGET)
