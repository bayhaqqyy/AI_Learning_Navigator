CXX ?= g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude
SOURCES = src/main.cpp src/algorithms.cpp src/data.cpp
TEST_SOURCES = tests/test_algorithms.cpp src/algorithms.cpp src/data.cpp

.PHONY: all test clean

all: bin/ai_learning_navigator

bin/ai_learning_navigator: $(SOURCES) | bin
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

bin/test_algorithms: $(TEST_SOURCES) | bin
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $@

test: bin/test_algorithms
	./bin/test_algorithms

bin:
	mkdir -p bin

clean:
	rm -f bin/ai_learning_navigator bin/test_algorithms
	rm -rf build
