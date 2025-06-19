
CXX := clang++-19

CXXFLAGS := -Wall -Wextra -Wreturn-type -Werror -std=c++23 -g

TARGET := main

SRC := main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
