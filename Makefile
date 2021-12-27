PROJECT_DIR ?=  $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
TARGET_LIB ?= lib$(shell basename $(PROJECT_DIR)).a

BUILD_DIR ?= ./build
INC_DIR ?= ./inc
SRC_DIR ?= ./src
TEST_DIR ?= ./tests

INCS := $(shell find $(INC_DIR) -regex '.+\.h')
SRCS := $(shell find $(SRC_DIR) -regex '.+\.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CC := clang
CFLAGS := -Wall -I$(INC_DIR) -I$$PWD
TEST_CFLAGS := -Wall -I$(INC_DIR) -I$$PWD
TEST_LDFLAGS := $(shell pkg-config --cflags --libs check)

AR := ar

MKDIR := mkdir
MKDIR_P := mkdir -p

.PHONY: build
build: $(BUILD_DIR)/$(TARGET_LIB)

$(BUILD_DIR)/$(TARGET_LIB): $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(BUILD_DIR)/%.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.c $(BUILD_DIR)/$(TARGET_LIB)
	$(MKDIR_P) $(dir $@)
	$(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) $< $(BUILD_DIR)/$(TARGET_LIB) -o $@

.PHONY: test/%
test/%: $(BUILD_DIR)/$(TEST_DIR)/%_test
	$<

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)