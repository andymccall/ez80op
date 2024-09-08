# Makefile for C Project with Profiling

# Project Configuration
BIN_NAME = ez80op
X86_PROJECT_NAME = ez80op_x86_64
ARMHF_PROJECT_NAME = ez80op_armhf
ARM64_PROJECT_NAME = ez80op_aarch64

# Architecture-Specific Compilers and Flags
X86_CC = gcc
ARM64_CC = aarch64-linux-gnu-gcc
ARMHF_CC = arm-linux-gnueabi-gcc
X86_CFLAGS = -Wall -g
ARM64_CFLAGS = -static
ARMHF_CFLAGS = -static

# Directories
SRC_DIR = src
OBJ_DIR = obj
OBJ_X86_DIR = x86
OBJ_ARM64_DIR = arm64
OBJ_ARMHF_DIR = armhf
BIN_DIR = bin
TEST_DIR = tests
RELEASE_DIR = release

# Source and Object Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
X86_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_X86_DIR)/%.o, $(SOURCES))
ARM64_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_ARM64_DIR)/%.o, $(SOURCES))
ARMHF_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_ARMHF_DIR)/%.o, $(SOURCES))


# Test Files and Object Files (if using Unity, adjust accordingly)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SOURCES))

# Include Directories
INCLUDES = -Iinclude # Adjust if you have additional include directories


# Unity Library (if using Unity for testing)
UNITY_DIR = path/to/unity # Update with the actual path
UNITY_LIB = $(UNITY_DIR)/unity.c

# Targets

all: $(X86_PROJECT_NAME) $(ARM64_PROJECT_NAME) $(ARMHF_PROJECT_NAME)

x86: CFLAGS += $(X86_CFLAGS)
x86: CC = $(X86_CC)
x86: $(X86_PROJECT_NAME)

$(X86_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_X86_DIR) $(X86_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(X86_OBJECTS) -o $(BIN_DIR)/$@ $(LDFLAGS)

# Architecture-Specific Targets

arm64: CFLAGS += $(ARM64_CFLAGS)
arm64: CC = $(ARM64_CC)
arm64: $(ARM64_PROJECT_NAME)

$(ARM64_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_ARM64_DIR) $(ARM64_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(ARM64_OBJECTS) -o $(BIN_DIR)/$@ $(LDFLAGS)

armhf: CFLAGS += $(ARMHF_CFLAGS)
armhf: CC = $(ARMHF_CC)
armhf: $(ARMHF_PROJECT_NAME)

$(ARMHF_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_ARMHF_DIR) $(ARMHF_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(ARMHF_OBJECTS) -o $(BIN_DIR)/$@ $(LDFLAGS)

# Testing Target (adjust if using a different testing framework)

test: $(TEST_OBJECTS) $(OBJECTS) $(UNITY_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Release Target (optimize for performance)

release_x86: CFLAGS += -O2 -DNDEBUG
release_x86: $(RELEASE_DIR) x86

release_arm64: CFLAGS += -O2 -DNDEBUG
release_arm64: $(RELEASE_DIR) arm64

release_armhf: CFLAGS += -O2 -DNDEBUG
release_armhf: $(RELEASE_DIR) armhf

# Profiling Target (compile with profiling flags)

profile: CFLAGS += -pg
profile: $(X86_PROJECT_NAME)
	./$(X86_PROJECT_NAME) # Run the executable to generate profiling data
	gprof $(X86_PROJECT_NAME) gmon.out > analysis.txt # Analyze the profiling data

# Packaging Target (customize as needed)

package: package_x86 package_arm64 package_armhf

package_x86: release_x86
	tar -zcvf $(RELEASE_DIR)/$(X86_PROJECT_NAME).tar.gz --transform 's/bin\/$(X86_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(X86_PROJECT_NAME)

package_arm64: release_arm64
	tar -zcvf $(RELEASE_DIR)/$(ARM64_PROJECT_NAME).tar.gz --transform 's/bin\/$(ARM64_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(ARM64_PROJECT_NAME)

package_armhf: release_armhf
	tar -zcvf $(RELEASE_DIR)/$(ARMHF_PROJECT_NAME).tar.gz --transform 's/bin\/$(ARMHF_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(ARMHF_PROJECT_NAME)

# Cleanup Target

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_DIR) $(RELEASE_DIR) $(X86_PROJECT_NAME) $(ARM64_PROJECT_NAME) $(ARMHF_PROJECT_NAME) $(TEST_EXECUTABLE) analysis.txt gmon.out

# Create directories

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_X86_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_ARM64_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_ARMHF_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(TEST_DIR):
	mkdir -p $@

$(RELEASE_DIR):
	mkdir -p $@

# Object File Compilation Rules

$(OBJ_DIR)/$(OBJ_X86_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(OBJ_ARM64_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(OBJ_ARMHF_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@