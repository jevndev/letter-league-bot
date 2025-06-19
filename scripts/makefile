CXX := clang++-19

CXXFLAGS := -Wall -Wextra -Wreturn-type -Werror -std=c++23

SRC := main.cpp

BUILD_DIR := build

DEBUG_DIR := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release

debug: CXXFLAGS += -g -O0 -pg
debug: $(DEBUG_DIR)/main

release: CXXFLAGS += -O3
release: $(RELEASE_DIR)/main

$(DEBUG_DIR)/main: $(SRC)
	mkdir -p $(DEBUG_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(RELEASE_DIR)/main: $(SRC)
	mkdir -p $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
