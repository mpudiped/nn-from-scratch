CC = clang
CFLAGS = -std=c17 -MMD -MP  -Wall -Wextra -Wpedantic
LDFLAGS =
LDLIBS = -lm

# debug mode adds debugging info and compiles unoptimized with sanitization
MODE ?= debug
ifeq ($(MODE),debug)
CFLAGS += -fsanitize=address,undefined -fno-sanitize-recover=undefined -g -O0
LDFLAGS += -fsanitize=address,undefined
BUILD_DIR = build/debug
else ifeq ($(MODE),release)
CFLAGS += -O2
BUILD_DIR = build/release
else
$(error ERROR: MODE must be debug or release, not $(MODE))
endif

# 1. DYNAMIC FILE DISCOVERY
# Finds all .c files in the ./src folder automatically
SRCS := $(wildcard src/*.c)
# Transforms "./src/main.c" into "$(BUILD_DIR)/main.o" dynamically
objects := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))
# Transforms objects list into a .d list for dependencies
deps = $(objects:.o=.d)

# Same principles applied to the test files
TEST_SRCS := $(wildcard tests/*.c)
test_objects := $(patsubst tests/%.c,$(BUILD_DIR)/%.o,$(TEST_SRCS))
test_objects += $(objects)
test_objects := $(filter-out $(BUILD_DIR)/main.o,$(test_objects))
test_deps = $(test_objects:.o=.d)

# --- RULES ---

$(BUILD_DIR)/hello: $(objects)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


.PHONY: clean test run
clean:
	rm -rf ./build
test: $(BUILD_DIR)/test
	$(BUILD_DIR)/test
run: $(BUILD_DIR)/hello
	$(BUILD_DIR)/hello

$(BUILD_DIR)/test: $(test_objects)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: tests/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(deps) $(test_deps)