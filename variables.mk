PROJECT_DIR ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
TARGET_LIB ?= lib$(shell basename $(PROJECT_DIR)).a

DOCKER_IMAGE ?= $(shell basename $(PROJECT_DIR))_build

BUILD_DIR ?= ./build
INC_DIR ?= ./inc
SRC_DIR ?= ./src
LIB_DIR ?= ./lib
TEST_DIR ?= ./tests

INCS := $(shell find $(INC_DIR) -regex '.+\.h')
SRCS := $(shell find $(SRC_DIR) -regex '.+\.c')
LIBS_SRCS := $(shell find $(LIB_DIR) -mindepth 1 -maxdepth 1 -type d)
LIBS := $(LIBS_SRCS:%=$(BUILD_DIR)/%)
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC ?= clang
CFLAGS ?=
CFLAGS := $(CFLAGS) -Wall -I$(INC_DIR) -I$$PWD
TEST_CFLAGS := -Wall -I$(INC_DIR) -I$$PWD
TEST_LDFLAGS := $(shell pkg-config --cflags --libs check)

AR := ar

MKDIR := mkdir
MKDIR_P := mkdir -p
