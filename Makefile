BUILD_DIR = ./build
$(shell mkdir -p $(BUILD_DIR))

GCC = clang
INC_PATH = 
CXXFLAGS = -Wall -Werror -O3 -MMD -lstdc++
INCFLAGS = $(addprefix -I, $(INC_PATH))
BIN = $(BUILD_DIR)/CacheSim
CSRCS = $(shell find $(abspath ./src) -name "*.c" -or -name "*.cpp" -or -name "*.cc")


build:
	$(GCC) $(CXXFLAGS) $(CSRCS) -o $(BIN)

run: build
	$(BIN)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: build run