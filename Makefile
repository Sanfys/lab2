CXX      = g++
CXXFLAGS = -std=c++17 -O2 -pthread -Wall
SRCS     = $(wildcard src/*.cpp)
BINS     = $(patsubst src/%.cpp,build/%,$(SRCS))

all: $(BINS)

build/%: src/%.cpp src/common.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build
