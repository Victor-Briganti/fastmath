CXX := clang++
CXXFLAGS := -fPIC
RLFLAGS := -O3
DBFLAGS := -g -Wall -Wshadow -Wconversion -Wextra -Wunreachable-code -Wunused -Wcast-align
INCLUDES := -Iinclude/

LIB_NAME := fastmath
SHARED_LIB := lib$(LIB_NAME).so

BUILD_TYPE ?= release

ifeq ($(BUILD_TYPE), debug)
	CXXFLAGS += $(DBFLAGS)
else ifeq ($(BUILD_TYPE), release)
	CXXFLAGS += $(RLFLAGS)
endif

SRC_DIR := src
OBJ_DIR := build
TEST_OBJ_DIR := $(OBJ_DIR)/test
BENCH_OBJ_DIR := $(OBJ_DIR)/bench

PATH_LIB := $(OBJ_DIR)
LDPATH := -Wl,-rpath=$(PATH_LIB)
LIB_PATH := $(PATH_LIB)/$(SHARED_LIB)

all: shared

shared: $(LIB_PATH)

$(LIB_PATH): | $(OBJ_DIR)
	$(CXX) -shared -o $@ $(SRC_DIR)/*.cpp $(CXXFLAGS) $(INCLUDES)

$(OBJ_DIR):
	@mkdir -p $@

$(TEST_OBJ_DIR): | $(OBJ_DIR)
	@mkdir -p $@

$(BENCH_OBJ_DIR): | $(OBJ_DIR)
	@mkdir -p $@

test: test_sqrt test_log2 test_log test_log10 test_exp test_exp2 test_pow test_sin test_cos test_tan test_atan test_asin test_acos test_sinh test_cosh test_tanh

test_sqrt: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/sqrt.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_log2: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/log2.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_log: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/log.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_log10: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/log10.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_exp: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/exp.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_exp2: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/exp2.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_pow: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/pow.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_sin: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/sin.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_cos: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/cos.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_tan: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/tan.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_atan: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/atan.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_asin: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/asin.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_acos: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/acos.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_sinh: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/sinh.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_cosh: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/cosh.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

test_tanh: $(LIB_PATH) | $(TEST_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) test/tanh.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(TEST_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_cos: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/cos.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_cosf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/cosf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_sin: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/sin.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_sinf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/sinf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_tan: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/tan.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_tanf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/tanf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_acos: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/acos.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_acosf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/acosf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_asin: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/asin.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_asinf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/asinf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_atan: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/atan.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_atanf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/atanf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_cosh: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/cosh.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_coshf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/coshf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_sinh: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/sinh.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_sinhf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/sinhf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_tanh: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/tanh.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_tanhf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/tanhf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_exp: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/exp.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_expf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/expf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_exp2: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/exp2.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_exp2f: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/exp2f.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_log: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/log.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_logf: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/logf.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_log2: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/log2.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_log2f: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/log2f.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_log10: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/log10.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

bench_error_log10f: $(LIB_PATH) | $(BENCH_OBJ_DIR)
	$(CXX) $(DBFLAGS) $(INCLUDES) bench/error/log10f.cpp -L$(PATH_LIB) -l$(LIB_NAME) -o $(BENCH_OBJ_DIR)/$@ -lm $(LDPATH)

debug:
	$(MAKE) BUILD_TYPE=debug

release:
	$(MAKE) BUILD_TYPE=release

clean:
	@rm -rf build/

.PHONY: all debug release shared clean
