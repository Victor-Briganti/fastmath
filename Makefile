CXX := clang++
INCLUDES := -Iinclude/

CXXFLAGS :=
RLFLAGS  := -O3
DBFLAGS  := -g -Wall -Wshadow -Wconversion -Wextra -Wunreachable-code -Wunused -Wcast-align

BUILD_TYPE ?= release
USE_FASTMATH ?= 0

ifeq ($(USE_FASTMATH), 1)
  CXXFLAGS += -ffast-math -fno-finite-math-only
endif

ifeq ($(BUILD_TYPE), debug)
  CXXFLAGS += $(DBFLAGS)
else
  CXXFLAGS += $(RLFLAGS)
endif

LIB_NAME   := fastmath
SHARED_LIB := lib$(LIB_NAME).so

SRC_DIR := src
OBJ_DIR := build
OUT_DIR := output

PATH_LIB := $(OBJ_DIR)
LIB_PATH := $(PATH_LIB)/$(SHARED_LIB)

LDPATH := -Wl,-rpath=$(PATH_LIB)
LIBS   := -L$(PATH_LIB) -l$(LIB_NAME) -lm $(LDPATH)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

TEST_OBJ_DIR  := $(OBJ_DIR)/test
BENCH_OBJ_DIR := $(OBJ_DIR)/bench

FUNCTIONS := sin cos tan atan asin acos sinh cosh tanh exp exp2 log log2 log10 pow sqrt

TEST_BINS := $(addprefix $(TEST_OBJ_DIR)/test_, $(FUNCTIONS))

BENCH_ERROR_BINS := \
  $(addprefix $(BENCH_OBJ_DIR)/bench_error_, $(FUNCTIONS))

BENCH_SPEED_BINS := \
		$(addprefix $(BENCH_OBJ_DIR)/bench_speed_, $(FUNCTIONS))

all: shared

shared: $(LIB_PATH)

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		$$t; \
		done

bench_error: output | $(BENCH_ERROR_BINS)
	@for bench in $(BENCH_ERROR_BINS); do \
		echo "Running $$bench"; \
		$$bench; \
		done

bench_speed: output | $(BENCH_SPEED_BINS)
	@for bench in $(BENCH_SPEED_BINS); do \
		echo "Running $$bench"; \
		$$bench; \
		done

output:
	@mkdir -p $(OUT_DIR)/speed/double
	@mkdir -p $(OUT_DIR)/speed/float
	@mkdir -p $(OUT_DIR)/error/double
	@mkdir -p $(OUT_DIR)/error/float

debug:
	$(MAKE) BUILD_TYPE=debug

release:
	$(MAKE) BUILD_TYPE=release

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OUT_DIR)

$(LIB_PATH): $(SRCS) | $(OBJ_DIR)
	$(CXX) -shared -o $@ $^ -fPIC $(CXXFLAGS) $(INCLUDES)

$(TEST_OBJ_DIR)/test_%: test/%.cpp $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< $(LIBS) -o $@

$(BENCH_OBJ_DIR)/bench_error_%: bench/error/%.cpp $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< $(LIBS) -o $@

$(BENCH_OBJ_DIR)/bench_speed_%: bench/speed/%.cpp $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< $(LIBS) -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(TEST_OBJ_DIR): | $(OBJ_DIR)
	@mkdir -p $@

$(BENCH_OBJ_DIR): | $(OBJ_DIR)
	@mkdir -p $@

.PHONY: all shared test bench_error debug release clean
