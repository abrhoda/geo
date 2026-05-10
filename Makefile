DEBUG ?= 0
NAME := geo
INCLUDE_DIR := ./include
SRC_DIR := ./src
TEST_DIR := ./test
#BUILD_DIR := build
BIN_DIR := ./bin
FORMATTER := clang-format
LINTER := clang-tidy

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
CFLAGS += -std=c99

#set headers dir
CFLAGS += -I$(INCLUDE_DIR)

# poor man's static analyzer
CFLAGS += -Wpedantic -pedantic-errors -Werror -Wall -Wextra
CFLAGS += -Waggregate-return
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wdeclaration-after-statement
CFLAGS += -Wfloat-equal
CFLAGS += -Wformat=2
#CFLAGS += -Wlogical-op
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
TEST_CFLAGS += -std=c99 -g3 -O0 -fno-builtin -DGEO_TEST -I$(INCLUDE_DIR)

# Linker opts. Remember to set LDFLAGS before objs and LDLIBS after objs to avoid undefined refs when linking.
#LDFLAGS += -L/$(LIBS)/libspecific
LDLIBS += -lm

.PHONY: test-all
test-all: test-double test-float test-int test-long

.PHONY: test-double
test-double:
	@$(CC) $(TEST_CFLAGS) $(TEST_DIR)/test_geo_double.c $(SRC_DIR)/geo_double.c $(LDLIBS) -o $(BIN_DIR)/test_geo_double
	@$(BIN_DIR)/test_geo_double

.PHONY: test-float
test-float:
	@$(CC) $(TEST_CFLAGS) $(TEST_DIR)/test_geo_float.c $(SRC_DIR)/geo_float.c $(LDLIBS) -o $(BIN_DIR)/test_geo_float
	@$(BIN_DIR)/test_geo_float

.PHONY: test-int
test-int:
	@$(CC) $(TEST_CFLAGS) $(TEST_DIR)/test_geo_int.c $(SRC_DIR)/geo_int.c $(LDLIBS) -o $(BIN_DIR)/test_geo_int
	@$(BIN_DIR)/test_geo_int

.PHONY: test-long
test-long:
	@$(CC) $(TEST_CFLAGS) $(TEST_DIR)/test_geo_long.c $(SRC_DIR)/geo_long.c $(LDLIBS) -o $(BIN_DIR)/test_geo_long
	@$(BIN_DIR)/test_geo_long

.PHONY: format
format:
	$(FORMATTER) --style=file -i $(INCLUDE_DIR)/* $(SRC_DIR)/*

.PHONY: lint
lint:
	$(LINTER) --config-file=.clang-tidy $(SRC_DIR)/* -- $(CFLAGS) -Wmost

.PHONY: setup
setup:
	mkdir -p $(BIN_DIR)# $(BUILD_DIR) $(DEPS_DIR)

.PHONY: clean
clean:
	rm -f ./bin/*
