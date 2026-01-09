CXX := clang++
INCLUDES := -Iinclude/

CXXFLAGS := -fPIC
RLFLAGS  := -O3
DBFLAGS  := -g -Wall -Wshadow -Wconversion -Wextra -Wunreachable-code -Wunused -Wcast-align

BUILD_TYPE ?= release

ifeq ($(BUILD_TYPE), debug)
  CXXFLAGS += $(DBFLAGS)
else
  CXXFLAGS += $(RLFLAGS)
endif

LIB_NAME   := fastmath
SHARED_LIB := lib$(LIB_NAME).so

SRC_DIR := src
OBJ_DIR := build

PATH_LIB := $(OBJ_DIR)
LIB_PATH := $(PATH_LIB)/$(SHARED_LIB)

LDPATH := -Wl,-rpath=$(PATH_LIB)
LIBS   := -L$(PATH_LIB) -l$(LIB_NAME) -lm $(LDPATH)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

TEST_OBJ_DIR  := $(OBJ_DIR)/test
BENCH_OBJ_DIR := $(OBJ_DIR)/bench

TESTS := sqrt log2 log log10 exp exp2 pow \
         sin cos tan atan asin acos \
         sinh cosh tanh

TEST_BINS := $(addprefix $(TEST_OBJ_DIR)/test_, $(TESTS))

BENCH_FUNCS := \
  cos cosf sin sinf tan tanf \
  acos acosf asin asinf atan atanf \
  cosh coshf sinh sinhf tanh tanhf \
  exp expf exp2 exp2f \
  log logf log2 log2f log10 log10f \
  pow powf sqrt sqrtf

BENCH_ERROR_BINS := \
  $(addprefix $(BENCH_OBJ_DIR)/bench_error_, $(BENCH_FUNCS))

BENCH_SPEED_BINS := \
		$(addprefix $(BENCH_OBJ_DIR)/bench_speed_, $(BENCH_FUNCS))

all: shared

shared: $(LIB_PATH)

test: $(TEST_BINS)

bench_error: $(BENCH_ERROR_BINS)

bench_speed: $(BENCH_SPEED_BINS)

debug:
	$(MAKE) BUILD_TYPE=debug

release:
	$(MAKE) BUILD_TYPE=release

clean:
	@rm -rf $(OBJ_DIR)

$(LIB_PATH): $(SRCS) | $(OBJ_DIR)
	$(CXX) -shared -o $@ $^ $(CXXFLAGS) $(INCLUDES)

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
