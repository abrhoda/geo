DEBUG ?= 0
NAME := geo
#INCLUDE_DIR := include
SRC_DIR := src
TEST_DIR := test
#BUILD_DIR := build
BIN_DIR := bin

# For containing make's dependency (.d) files. Read more here: https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
#DEPS_DIR := deps

# Set Clang Options
#CC = clang
#CFLAGS += -std=c89
#CFLAGS += -Wpedantic
#CFLAGS += -Werror
#CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -Wmost

# set c standard
CFLAGS += -std=c89

#set headers dir
#CFLAGS += -I./$(INCLUDE_DIR)

# poor man's static analyzer
CFLAGS += -Wpedantic -pedantic-errors -Werror -Wall -Wextra
CFLAGS += -Waggregate-return
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wdeclaration-after-statement
CFLAGS += -Wfloat-equal
CFLAGS += -Wformat=2
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-declarations
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wnested-externs
CFLAGS += -Wpointer-arith
CFLAGS += -Wredundant-decls
CFLAGS += -Wsequence-point
CFLAGS += -Wshadow
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wswitch
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wunused-but-set-parameter
CFLAGS += -Wwrite-strings
CFLAGS += -fno-builtin

# Optimization settings
ifeq ($(DEBUG), 1)
	CFLAGS := $(CFLAGS) -g -O0
else
	CFLAGS := $(CFLAGS) -O3 -DNDEBUG
endif

# Test specific set of flags for maximum debug potential with TEST macro defined
# for potential use in code.
TEST_CFLAGS += -std=c89 -g3 -O0 -fno-builtin -DTEST

# Linker opts. Remember to set LDFLAGS before objs and LDLIBS after objs to avoid undefined refs when linking.
#LDFLAGS += -L/$(LIBS)/libspecific
LDLIBS += -lm

.PHONY: test
test:
	@$(CC) $(TEST_CFLAGS) $(TEST_DIR)/test_geo.c $(SRC_DIR)/geo.c $(LDLIBS) -o $(BIN_DIR)/test_geo
	@$(BIN_DIR)/test_geo


.PHONY: setup
setup:
	mkdir -p $(BIN_DIR)# $(BUILD_DIR) $(DEPS_DIR)

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*
