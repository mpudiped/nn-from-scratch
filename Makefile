CC = clang
CFLAGS = -std=c17 -MMD -MP  -Wall -Wextra 
LDFLAGS =
LDLIBS = -lm

# debug mode adds debugging info and compiles unoptimized with sanitization
MODE ?= debug
ifeq ($(MODE),debug)
CFLAGS += -fsanitize=address,undefined -fno-sanitize-recover=undefined -g -O0
LDFLAGS += -fsanitize=address,undefined
BUILD_DIR = ./build/debug
else ifeq ($(MODE),release)
CFLAGS += -O2
BUILD_DIR = ./build/release
else
$(error ERROR: invalid MODE arg)
endif

# 1. DYNAMIC FILE DISCOVERY
# Finds all .c files in the ./src folder automatically
SRCS := $(wildcard ./src/*.c)
# Transforms "./src/main.c" into "$(BUILD_DIR)/main.o" dynamically
objects := $(patsubst ./src/%.c,$(BUILD_DIR)/%.o,$(SRCS))
# Transforms objects list into a .d list for dependencies
deps = $(objects:.o=.d)

target = $(BUILD_DIR)/hello

# --- RULES ---

$(target): $(objects)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: ./src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


.PHONY: clean
clean:
	rm -rf $(target) ./build

-include $(deps)