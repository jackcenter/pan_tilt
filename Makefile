TARGET ?= practice

BUILD_DIR := ./build
TGT_DIR := ./
SRC_DIR := ./src
INC_DIR := ./include

TEST_TGT_DIR := $(BUILD_DIR)/test/tests
TEST_DIR := ./test

SRCS := $(wildcard $(SRC_DIR)/*.cpp)	# Find all c files
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)	# make object files for all c files 

CXX ?= $(CROSS_COMPILE)g++
LDFLAGS ?=
CXXFLAGS ?= -g -Wall -Werror -O0 -I$(INC_DIR)

define build_test
$(eval target := $1)
$(eval source := $2)

$(target): $(target).o
	$(CXX) $(target).o $(LDFLAGS) -o $(target)

$(target).o: $(source)
	mkdir -p $(dir $(target))
	$(CXX) $(CXXFLAGS) -c $(source) -o $(target).o
endef

all: $(TGT_DIR)/$(TARGET)

# Target to build final executable
$(TGT_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# Target to build the object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# List tests here
test: $(TEST_TGT_DIR)/test_utilities

# Build tests here
$(eval $(call build_test, $(TEST_TGT_DIR)/test_utilities, $(TEST_DIR)/test_utilities.cpp))

.PHONY: clean
clean:
	@if [ -d "${BUILD_DIR}" ]; \
	then \
		rm -r ${BUILD_DIR}; \
	fi
	@if [ -f "$(TGT_DIR)/$(TARGET)" ]; \
	then \
		rm -f $(TGT_DIR)/$(TARGET); \
	fi
