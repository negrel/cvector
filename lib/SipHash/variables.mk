PROJECT_DIR ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
TARGET_LIB ?= lib$(shell basename $(PROJECT_DIR)).a

BUILD_DIR ?= ./build
INC_DIR ?= ./src
SRC_DIR ?= ./src
LIB_DIR ?= ./lib
TEST_DIR ?= ./tests

INCS := $(shell find $(INC_DIR) -regex '.+\.h')
SRCS := $(SRC_DIR)/siphash.c $(SRC_DIR)/halfsiphash.c
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC ?= gcc
CFLAGS ?=
CFLAGS := $(CFLAGS) -Wall -I$(INC_DIR) -I$$PWD

AR := ar

MKDIR := mkdir
MKDIR_P := mkdir -p
