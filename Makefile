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
TEST_DIR := test
TEST_OBJ_DIR := $(OBJ_DIR)/test

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

debug:
	$(MAKE) BUILD_TYPE=debug

release:
	$(MAKE) BUILD_TYPE=release

clean:
	@rm -rf build/

.PHONY: all debug release shared clean
