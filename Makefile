CXX := g++
CXXFLAGS := -std=c++20 -ggdb3 -O0 
LIBS := -lraylib
INC := -Iinclude

TARGET := main
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
